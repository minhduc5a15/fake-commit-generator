#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *path = "./data.json";

int is_valid_date(struct tm *date) {
    struct tm start_date = {0};
    struct tm end_date = {0};

    start_date.tm_year = 2019 - 1900;
    start_date.tm_mon = 0;
    start_date.tm_mday = 1;

    end_date.tm_year = 2024 - 1900;
    end_date.tm_mon = 11;
    end_date.tm_mday = 13;

    const time_t start_time = mktime(&start_date);
    const time_t end_time = mktime(&end_date);
    const time_t current_time = mktime(date);

    return (current_time >= start_time && current_time <= end_time);
}

void write_to_json(const char *date) {
    FILE *file = fopen(path, "w");
    if (file) {
        fprintf(file, "{ \"date\": \"%s\" }\n", date);
        fclose(file);
    } else {
        perror("Error opening file for writing");
    }
}

void mark_commit(const char *date) {
    write_to_json(date);

    char git_add_cmd[256];
    snprintf(git_add_cmd, sizeof(git_add_cmd), "git add %s", path);
    system(git_add_cmd);

    char git_commit_cmd[512];
    snprintf(git_commit_cmd, sizeof(git_commit_cmd), "git commit -m \"%s\" --date=\"%s\"", date, date);
    system(git_commit_cmd);
}

void make_commits(int num_commits) {
    srand(time(NULL));

    struct tm base_date = {0};
    base_date.tm_year = 2019 - 1900;
    base_date.tm_mon = 0;  // January
    base_date.tm_mday = 1;

    for (int i = 0; i < num_commits; ++i) {
        int random_weeks = rand() % (54 * 4);
        int random_days = rand() % 7;

        struct tm random_date = base_date;
        random_date.tm_mday += random_weeks * 7 + random_days;
        mktime(&random_date); 

        if (is_valid_date(&random_date)) {
            char iso_date[20];
            strftime(iso_date, sizeof(iso_date), "%Y-%m-%dT%H:%M:%S", &random_date);
            printf("Creating commit: %s\n", iso_date);
            mark_commit(iso_date);
        } else {
            printf("Invalid date, skipping...\n");
        }
    }

    printf("Done! Pushing changes...\n");
    system("git push");
}

int main() {
    int num_commits;
    printf("Enter the number of commits to generate: ");
    if (scanf("%d", &num_commits) != 1 || num_commits <= 0) {
        printf("Error: Number of commits must be greater than 0.\n");
        return 1;
    }

    make_commits(num_commits);
    return 0;
}
