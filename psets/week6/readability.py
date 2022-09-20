from cs50 import get_string

def main():
    text = get_string("Text: ")

    lettercount = letterCount(text)
    wordcount = wordCount(text)
    sentencecount = sentenceCount(text)

    # 0.0588 * LettersPer100Words - 0.296 * SentencesPer100Words - 15.8

    lpw = lettercount * 100 // wordcount
    spw = sentencecount * 100 // wordcount

    grade = round(0.0588 * lpw - 0.296 * spw - 15.8)

    if grade < 1:
        return "Before Grade 1"
    elif grade > 16:
        return "Grade 16+"

    return f"Grade {grade}"

def letterCount(txt):
    count = 0
    for i in range(len(txt)):
        if txt[i].isalpha():
            count += 1
    return count

def wordCount(txt):
    count = 0
    foundLetter = False
    for i in range(len(txt)):
        if txt[i] == ' ':
            foundLetter = False
        else:
            if not(foundLetter):
                count += 1
                foundLetter = True
    return count

def sentenceCount(txt):
    count = 0
    for i in range(len(txt)):
        if txt[i] == '?' or txt[i] == '!' or txt[i] == '.':
            count += 1
    return count

print(main())
