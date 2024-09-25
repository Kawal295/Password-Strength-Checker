#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
void suggestion(const char* passwd, int* lowerCount, int* upperCount, int* numberCount, int* specialCount);
int crackingTime(const char* passwd, int lowerCount, int upperCount, int numberCount, int specialCount);
void strength(const char* passwd, int time_in_seconds);
bool password_length(const char* passwd);
int main() {
    char password[100];
    int lowerCount = 0, upperCount = 0, numberCount = 0, specialCount = 0;
    while (true) {
        printf("Enter a password: ");
        scanf("%99s", password); 
        if (!password_length(password)) {
            continue;  
        }
        suggestion(password, &lowerCount, &upperCount, &numberCount, &specialCount);
        long time_in_seconds = crackingTime(password, lowerCount, upperCount, numberCount, specialCount);
        strength(password, time_in_seconds);
    }

    return 0;
}
void suggestion(const char* passwd, int* lowerCount, int* upperCount, int* numberCount, int* specialCount) {
    bool has_upper = false, has_lower = false, has_digit = false, has_special = false;

    *lowerCount = 0;
    *upperCount = 0;
    *numberCount = 0;
    *specialCount = 0;

    for (int i = 0; passwd[i] != '\0'; i++) {
        if (isupper(passwd[i])) {
            has_upper = true;
            (*upperCount)++;
        } else if (islower(passwd[i])) {
            has_lower = true;
            (*lowerCount)++;
        } else if (isdigit(passwd[i])) {
            has_digit = true;
            (*numberCount)++;
        } else {
            has_special = true;
            (*specialCount)++;
        }
    }
    printf("Suggestion - ");
    if (!has_upper) 
        printf("Add at least one uppercase letter.\n");
    if (!has_lower) 
        printf("Add at least one lowercase letter.\n");
    if (!has_digit) 
        printf("Add at least one number.\n");
    if (!has_special) 
        printf("Add at least one special character.\n");
}
int crackingTime(const char* passwd, int lowerCount, int upperCount, int numberCount, int specialCount) {
    long long r = 0;
    if (lowerCount > 0) 
        r += pow(26, lowerCount);
    if (upperCount > 0) 
        r += pow(26, upperCount);
    if (numberCount > 0) 
        r += pow(10, numberCount);
    if (specialCount > 0) 
        r += pow(31, specialCount);
        
    double time_in_seconds = (double)r / 1000;  
    int time_in_minutes = time_in_seconds / 60;
    int time_in_hours = time_in_minutes / 60;
    int time_in_days = time_in_hours / 24;
    int time_in_weeks = time_in_days / 7;
    int time_in_months = time_in_days / 30; 
    int time_in_years = time_in_days / 365; 
    printf("Average Cracking Time is ");
    if (time_in_seconds < 60) {
        printf("%.0f seconds\n", time_in_seconds);
    } else if (time_in_minutes < 60) {
        printf("%ld Minutes\n", time_in_minutes);
    } else if (time_in_hours < 24) {
        printf("%ld Hours\n", time_in_hours);
    } else if (time_in_days < 30) {
        printf("%ld Days\n", time_in_days);
    } else if (time_in_weeks < 7) {
        printf("%ld Weeks\n", time_in_weeks);
    } else if (time_in_months < 12) {
        printf("%ld Months\n", time_in_months);
    } else {
        printf("%ld Years\n", time_in_years);
    }
    return time_in_seconds;
}
bool password_length(const char* passwd) {
    if (strlen(passwd) < 8) {
        printf("Password must be at least 8 characters\n");
        return false;
    }
    return true;
}
void strength(const char* passwd, int time_in_seconds){
    printf("Password Strength is ");
    if (time_in_seconds < 3600) {
        printf("Very Weak\n", passwd);
    } else if (time_in_seconds < 86400) {
        printf("Weak\n", passwd);
    } else if (time_in_seconds < 604800) {
        printf("Moderate\n", passwd);
    } else if (time_in_seconds < 7257600) {
        printf("Strong\n", passwd);
    } else {
        printf("Very Strong\n", passwd);
    }
}
