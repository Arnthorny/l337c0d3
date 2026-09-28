#include <stdio.h>
    int countSeniors(char** details, int detailsSize) {
    int i, tmp_age = 0, snr_cnt = 0;
    char *c_deet = 0;
    
    for (i = 0; i < detailsSize; i++)
        {
            c_deet = details[i];

            tmp_age = (10 * (c_deet[11] - '0')) + (c_deet[12] - '0');
            printf("%d\n", tmp_age);
            if (tmp_age > 60) snr_cnt++;
        }
        return snr_cnt;
    }

int main(void) {

    char *details[] = {"7868190130M7522","5303914400F9211","9273338290F4010"};
    
    countSeniors(details, 3);

    return 0;
}