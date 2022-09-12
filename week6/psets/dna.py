import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py [CSV FILE] [TEXTFILE]")
        sys.exit(1)

    # TODO: Read database file into a variable
    reader = open(sys.argv[1], "r")
    database = csv.DictReader(reader)
    # TODO: Read DNA sequence file into a variable
    file = open(sys.argv[2], "r")
    sequence = file.read()
    # TODO: Find longest match of each STR in DNA sequence
    strands = {}
    str_list = database.fieldnames[1:]
    for i in str_list:
        strands[i] = longest_match(sequence, i)
    # TODO: Check database for matching profiles
    for people in database:
        flag = False
        for j in str_list:
            if int(people[j]) == int(strands[j]):
                flag = True
            else:
                flag = False
                break
        if flag:
            print(people["name"])
            sys.exit(0)
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
