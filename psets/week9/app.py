# Made some improvements and bug fixes on Buy and Purchase
# Implemented INDEX.HTML front-end, some new back-end bugs appeared
# Shares bug fixed
# Implement SELL.HTML front & back-end
# Implement HISTORY.HTML front-end


import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    symb_list = []
    try:
        symbols = db.execute("SELECT symbol from owned where id = ?", session["user_id"])
        for i in symbols:
            symb_list.append(i["symbol"])
    except:
        return apology("No stocks owned")

    stonk = []
    cash = db.execute("select cash from users where id = ?", session["user_id"])[0]["cash"]
    for i in symb_list:
        s = {}
        stock = lookup(i)
        s["name"] = stock["name"]
        s["symbol"] = i
        s["price"] = db.execute("SELECT price FROM owned WHERE id = ? AND symbol = ?", session["user_id"], i)[0]["price"]
        s["shares"] = db.execute("SELECT amount FROM owned WHERE symbol = ? AND id = ?", i, session["user_id"])[0]["amount"]
        print(s["shares"])
        stonk.append(s)
    return render_template("index.html", stonk=stonk, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return quote()
    else:
        stock = quote()[1]
        return render_template("buy.html", name=stock["name"], price=stock["price"], symbol=stock["symbol"])


@app.route("/purchase", methods=["POST"])
@login_required
def purchase():
    """Confirm purchase"""
    cash = db.execute("select cash from users where id = ?", session["user_id"])[0]["cash"]
    shares = float(request.form.get("shares"))
    price = float(request.form.get("price"))
    symbol = request.form.get("symbol")
    if shares <= 0:
        return apology("Invalid number of shares")
    required = price * shares
    if cash < required:
        return apology("Brokey")


    count = db.execute("SELECT COUNT(*) FROM owned WHERE symbol = ?", symbol)

    if count[0]["COUNT(*)"] == 1:
        owned_shares = db.execute("SELECT amount FROM owned WHERE id = ?", session["user_id"])
        owned_shares = float(owned_shares[0]["amount"])
        newshares = owned_shares + shares
        db.execute("UPDATE owned SET amount = ? WHERE id = ?", newshares, session["user_id"])
        db.execute("UPDATE owned SET price = ? WHERE id = ?", price, session["user_id"])
    else:
        db.execute("INSERT INTO owned (id, amount, symbol, price) VALUES (?, ?, ?, ?)", session["user_id"], shares, symbol, price)

    """Add purchase to system history"""
    now = datetime.now()
    now = now.strftime("%d/%m/%Y %H:%M:%S")
    db.execute("INSERT INTO history (id, action, amount, price, date, symbol) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], "buy", shares, price, now, symbol)

    db.execute("UPDATE users SET cash = ? WHERE id = ?", cash-required, session["user_id"])

    return redirect("/")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    owned = db.execute("SELECT * FROM history WHERE id = ? ORDER BY date DESC", session["user_id"])
    return render_template("history.html", owned=owned)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol or symbol == " ":
            return apology("Need a symbol")

        stock = lookup(symbol.upper())
        if stock == None:
            return apology("Wrong symbol")
        return render_template("quoted.html", name=stock["name"], price=stock["price"], symbol=stock["symbol"]), stock


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    else:
        username = request.form.get("username")
        if not username or username == " ":
            return apology("TODO")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not password or password == " ":
            return apology("Must give password")
        if not confirmation or confirmation != password:
            return apology("Passwords do not match")
    hashed = generate_password_hash(password)
    try:
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashed)
    except:
        return apology("Username already exists")

    return redirect("/")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        return quote()
    else:
        stock = quote()[1]
        owned_shares = db.execute("SELECT amount FROM owned WHERE symbol = ? AND id = ?", stock["symbol"], session["user_id"])[0]["amount"]
        return render_template("sell.html", name=stock["name"], price=stock["price"], symbol=stock["symbol"], shares=owned_shares)

@app.route("/sellconfirm", methods=["GET", "POST"])
@login_required
def confirmSale():
    if request.method == "GET":
        return sell()
    else:
        price = float(request.form.get("price"))
        symbol = request.form.get("symbol")
        name = request.form.get("name")
        shares = float(request.form.get("shares"))
        owned_shares = db.execute("SELECT amount FROM owned WHERE symbol = ? AND id = ?", symbol, session["user_id"])[0]["amount"]

        if shares > owned_shares or shares <= 0:
            return apology("Invalid number of shares")

        cash_return = shares * price
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        """Remove ownership of shares from user"""
        if shares == owned_shares:
            db.execute("DELETE FROM owned WHERE symbol = ? AND id = ?", symbol, session["user_id"])
        else:
            remaining = owned_shares - shares
            db.execute("UPDATE owned SET amount = ? WHERE id = ? AND symbol = ?", remaining, session["user_id"], symbol)

        now = datetime.now()
        now = now.strftime("%d/%m/%Y %H:%M:%S")
        db.execute("INSERT INTO history (id, action, amount, price, date, symbol) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], "sell", shares, price, now, symbol)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash+cash_return, session["user_id"])
        return redirect("/")
