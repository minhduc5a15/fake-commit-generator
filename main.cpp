#include <boost/date_time/gregorian/gregorian.hpp>
#include <fstream>
#include <iostream>
#include <random>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;
namespace bg = boost::gregorian;

const string path = "./data.json";

bool is_valid_date(const bg::date &date) {
    const bg::date start_date(2019, 1, 1);
    const bg::date end_date(2024, 12, 13);
    return date >= start_date && date <= end_date;
}

void write_to_json(const string &date) {
    ofstream file(path);
    file << R"({ "date": ")" << date << "\" }" << endl;
    file.close();
}

void mark_commit(const string &date) {
    write_to_json(date);

    system(("git add " + path).c_str());
    system(("git commit -m \"" + date + "\" --date=\"" + date + "\"").c_str());
}

void make_commits(const int num_commits) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> weeks_dist(0, 54 * 4);
    uniform_int_distribution<> days_dist(0, 6);

    const bg::date base_date(2019, 1, 1);

    for (int i = 0; i < num_commits; ++i) {
        const int random_weeks = weeks_dist(gen);
        const int random_days = days_dist(gen);

        if (bg::date random_date = base_date + bg::weeks(random_weeks) + bg::days(random_days); is_valid_date(random_date)) {
            string iso_date = bg::to_iso_extended_string(random_date);
            cout << "Creating commit: " << iso_date << endl;
            mark_commit(iso_date);
        }
        else {
            cout << "Invalid date, skipping..." << endl;
        }
    }

    cout << "Done! Pushing changes..." << endl;
    system("git push");
}


int main() {
    int num_commits;
    cout << "Enter the number of commits to generate: ";
    cin >> num_commits;

    if (num_commits <= 0) {
        cout << "Error: Number of commits must be greater than 0." << endl;
        return 1;
    }

    make_commits(num_commits);
    return 0;
}
