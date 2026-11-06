#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

/* Αν δεν δοθεί ακέραιος, το πρόγραμμα σταματά. */
int diavase(void)
{
    int x;
    if (scanf("%d", &x) != 1) {
        printf("Χρειάζεται ακέραιος αριθμός.\n");
        exit(1);
    }
    return x;
}

int *desmefsi(int n)
{
    int *p = malloc((size_t)n * sizeof(int));
    if (p == NULL) {
        printf("Δεν υπάρχει αρκετή μνήμη.\n");
        exit(1);
    }
    return p;
}

void gemisma(int *a, int n)
{
    int i;
    for (i = 0; i < n; i++)
        *(a + i) = 30 + rand() % 471;
}

/* Το NULL σημαίνει ότι ο πίνακας δεν έχει δημιουργηθεί ακόμα. */
void ektiposi(const int *a, int n, const char *titlos)
{
    int i;
    if (a == NULL)
        return;
    printf("%s\n", titlos);
    for (i = 0; i < n; i++)
        printf("%d ", *(a + i));
    printf("\n");
}

int seiriaki(const int *a, int n, int x)
{
    int i;
    for (i = 0; i < n; i++) {
        if (*(a + i) == x)
            return i;
    }
    return -1;
}

/* Ταξινόμηση με καταμέτρηση: οι τιμές είναι από 30 έως 500. */
void taxinomisi(int *a, int n)
{
    int *metritis = calloc(471, sizeof(int));
    int i, timi, k = 0;
    if (metritis == NULL) {
        printf("Δεν υπάρχει αρκετή μνήμη.\n");
        exit(1);
    }
    for (i = 0; i < n; i++)
        (*(metritis + *(a + i) - 30))++;

    for (timi = 30; timi <= 500; timi++) {
        while (*(metritis + timi - 30) > 0) {
            *(a + k) = timi;
            k++;
            (*(metritis + timi - 30))--;
        }
    }
    free(metritis);
}

int *antigrafo(const int *a, int n)
{
    int *b = desmefsi(n);
    int i;
    for (i = 0; i < n; i++)
        *(b + i) = *(a + i);
    taxinomisi(b, n);
    return b;
}

int dyadiki(const int *a, int n, int x)
{
    int aristera = 0, dexia = n - 1, mesi;
    while (aristera <= dexia) {
        mesi = aristera + (dexia - aristera) / 2;
        if (*(a + mesi) == x)
            return mesi;
        if (x < *(a + mesi))
            dexia = mesi - 1;
        else
            aristera = mesi + 1;
    }
    return -1;
}

/* Ο δεύτερος πίνακας δημιουργείται και ελευθερώνεται εδώ. */
int *sygxonefsi(const int *a, int n)
{
    int *b = desmefsi(n);
    int *c = desmefsi(2 * n);
    int i = 0, j = 0, k = 0;
    gemisma(b, n);
    taxinomisi(b, n);
    ektiposi(b, n, "Προσωρινός ταξινομημένος πίνακας:");

    while (i < n && j < n) {
        if (*(a + i) <= *(b + j)) {
            *(c + k) = *(a + i);
            i++;
        } else {
            *(c + k) = *(b + j);
            j++;
        }
        k++;
    }
    for (; i < n; i++, k++)
        *(c + k) = *(a + i);
    for (; j < n; j++, k++)
        *(c + k) = *(b + j);
    free(b);
    return c;
}

/* Αρχείο κειμένου: πρώτα το μέγεθος και μετά τα στοιχεία. */
void apothikefsi(const int *a, int n)
{
    FILE *fp = fopen("pinakas.txt", "w");
    int i, sfalma;
    if (fp == NULL) {
        printf("Το αρχείο δεν ανοίγει.\n");
        return;
    }
    fprintf(fp, "%d\n", n);
    for (i = 0; i < n; i++)
        fprintf(fp, "%d\n", *(a + i));
    sfalma = ferror(fp);
    if (fclose(fp) != 0)
        sfalma = 1;
    if (sfalma)
        printf("Η αποθήκευση απέτυχε.\n");
    else
        printf("Αποθηκεύτηκε στο pinakas.txt.\n");
}

int *fortosi(int *n)
{
    FILE *fp = fopen("pinakas.txt", "r");
    int *a, megethos, i;
    if (fp == NULL) {
        printf("Το αρχείο δεν ανοίγει.\n");
        return NULL;
    }
    if (fscanf(fp, "%d", &megethos) != 1 ||
        megethos <= 0 || megethos > INT_MAX / 2) {
        fclose(fp);
        printf("Μη έγκυρο μέγεθος στο αρχείο.\n");
        return NULL;
    }
    a = desmefsi(megethos);
    for (i = 0; i < megethos; i++) {
        if (fscanf(fp, "%d", a + i) != 1 ||
            *(a + i) < 30 || *(a + i) > 500) {
            free(a);
            fclose(fp);
            printf("Μη έγκυρα στοιχεία στο αρχείο.\n");
            return NULL;
        }
    }
    fclose(fp);
    *n = megethos;
    return a;
}

int main(void)
{
    int n, epilogi, x, thesi;
    int *a, *b, *c = NULL, *neos;
    srand((unsigned int)time(NULL));
    do {
        printf("Μέγεθος πίνακα (θετικός ακέραιος): ");
        n = diavase();
    } while (n <= 0 || n > INT_MAX / 2);
    a = desmefsi(n);
    gemisma(a, n);
    /* Όπως στο παράδειγμα, δημιουργούμε από την αρχή ταξινομημένο αντίγραφο. */
    b = antigrafo(a, n);

    do {
        printf("\n1. Σειριακή αναζήτηση\n"
               "2. Ταξινόμηση αντιγράφου\n"
               "3. Δυαδική αναζήτηση\n"
               "4. Συγχώνευση\n"
               "5. Εκτύπωση πινάκων\n"
               "6. Αποθήκευση αρχικού πίνακα\n"
               "7. Φόρτωση αρχικού πίνακα\n"
               "0. Έξοδος\nΕπιλογή: ");
        epilogi = diavase();
        switch (epilogi) {
        case 1:
        case 3:
            printf("Τιμή προς αναζήτηση: ");
            x = diavase();
            if (epilogi == 1)
                thesi = seiriaki(a, n, x);
            else
                thesi = dyadiki(b, n, x);
            if (thesi == -1)
                printf("Δεν βρέθηκε.\n");
            else
                printf("Βρέθηκε στη θέση %d.\n", thesi + 1);
            break;
        case 2:
            free(b);
            b = antigrafo(a, n);
            ektiposi(b, n, "Ταξινομημένο αντίγραφο:");
            break;
        case 4:
            free(c);
            c = sygxonefsi(b, n);
            ektiposi(c, 2 * n, "Συγχωνευμένος πίνακας:");
            break;
        case 5:
            ektiposi(a, n, "Αρχικός πίνακας:");
            ektiposi(b, n, "Ταξινομημένο αντίγραφο:");
            ektiposi(c, 2 * n, "Συγχωνευμένος πίνακας:");
            break;
        case 6:
            apothikefsi(a, n);
            break;
        case 7:
            neos = fortosi(&n);
            if (neos != NULL) {
                free(a);
                free(b);
                free(c);
                a = neos;
                b = antigrafo(a, n);
                c = NULL;
                printf("Ο πίνακας φορτώθηκε.\n");
            }
            break;
        case 0:
            break;
        default:
            printf("Λάθος επιλογή.\n");
        }
    } while (epilogi != 0);

    free(a);
    free(b);
    free(c);
    return 0;
}
