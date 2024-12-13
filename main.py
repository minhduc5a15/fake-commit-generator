import json
import random
import subprocess
from datetime import datetime, timedelta

path = './data.json'

def is_valid_date(date):
    start_date = datetime(2019, 1, 1)
    end_date = datetime(2024, 12, 13)
    return start_date <= date <= end_date

def write_to_json(date):
    with open(path, 'w') as file:
        json.dump({"date": date}, file)

def mark_commit(date):
    write_to_json(date)
    subprocess.run(["git", "add", path])
    subprocess.run(["git", "commit", "-m", date, "--date", date])

def make_commits(num_commits):
    random.seed()
    base_date = datetime(2019, 1, 1)
    weeks_dist = random.randint(0, 54 * 4)  # Random weeks
    days_dist = random.randint(0, 6)  # Random days

    for _ in range(num_commits):
        random_weeks = random.randint(0, 54 * 4)
        random_days = random.randint(0, 6)

        random_date = base_date + timedelta(weeks=random_weeks) + timedelta(days=random_days)

        if is_valid_date(random_date):
            iso_date = random_date.isoformat()
            print(f"Creating commit: {iso_date}")
            mark_commit(iso_date)
        else:
            print("Invalid date, skipping...")

    print("Done! Pushing changes...")
    subprocess.run(["git", "push"])

def main():
    try:
        num_commits = int(input("Enter the number of commits to generate: "))
        if num_commits <= 0:
            print("Error: Number of commits must be greater than 0.")
            return
        make_commits(num_commits)
    except ValueError:
        print("Invalid input. Please enter a valid number.")

if __name__ == "__main__":
    main()
