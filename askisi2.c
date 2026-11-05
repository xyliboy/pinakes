#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

/* Διαβάζει έναν ακέραιο και απορρίπτει λανθασμένη είσοδο. */
int diavase(void)
{
    int x, c, ok;
    do {
        ok = scanf("%d", &x);
        if (ok == EOF)
            exit(0);
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        if (ok != 1)
            printf("Δώσε έναν ακέραιο: ");
    } while (ok != 1);
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

void ektiposi(const int *a, int n)
{
    int i;
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
    printf("Προσωρινός ταξινομημένος πίνακας:\n");
    ektiposi(b, n);

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
    while (i < n) {
        *(c + k) = *(a + i);
        i++;
        k++;
    }
    while (j < n) {
        *(c + k) = *(b + j);
        j++;
        k++;
    }
    free(b);
    return c;
}

/* Αρχείο κειμένου: πρώτα το μέγεθος και μετά τα στοιχεία. */
void apothikefsi(const int *a, int n)
{
    FILE *fp = fopen("pinakas.txt", "w");
    int i, ok = 1;
    if (fp == NULL) {
        printf("Το αρχείο δεν ανοίγει.\n");
        return;
    }
    if (fprintf(fp, "%d\n", n) < 0)
        ok = 0;
    for (i = 0; i < n; i++) {
        if (fprintf(fp, "%d\n", *(a + i)) < 0)
            ok = 0;
    }
    if (fclose(fp) != 0)
        ok = 0;
    if (ok)
        printf("Αποθηκεύτηκε στο pinakas.txt.\n");
    else
        printf("Η αποθήκευση απέτυχε.\n");
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
    int *a, *b = NULL, *c = NULL, *neos;
    srand((unsigned int)time(NULL));
    do {
        printf("Μέγεθος πίνακα (θετικός ακέραιος): ");
        n = diavase();
    } while (n <= 0 || n > INT_MAX / 2);
    a = desmefsi(n);
    gemisma(a, n);

    do {
        printf("\n1. Σειριακή αναζήτηση\n");
        printf("2. Ταξινόμηση αντιγράφου\n");
        printf("3. Δυαδική αναζήτηση\n");
        printf("4. Συγχώνευση\n");
        printf("5. Εκτύπωση πινάκων\n");
        printf("6. Αποθήκευση αρχικού πίνακα\n");
        printf("7. Φόρτωση αρχικού πίνακα\n");
        printf("0. Έξοδος\nΕπιλογή: ");
        epilogi = diavase();
        switch (epilogi) {
        case 1:
        case 3:
            if (epilogi == 3 && b == NULL) {
                printf("Επίλεξε πρώτα ταξινόμηση (2).\n");
                break;
            }
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
            printf("Το αντίγραφο ταξινομήθηκε.\n");
            break;
        case 4:
            if (b == NULL) {
                printf("Επίλεξε πρώτα ταξινόμηση (2).\n");
                break;
            }
            free(c);
            c = sygxonefsi(b, n);
            printf("Συγχωνευμένος πίνακας:\n");
            ektiposi(c, 2 * n);
            break;
        case 5:
            printf("Αρχικός πίνακας:\n");
            ektiposi(a, n);
            if (b != NULL) {
                printf("Ταξινομημένο αντίγραφο:\n");
                ektiposi(b, n);
            }
            if (c != NULL) {
                printf("Συγχωνευμένος πίνακας:\n");
                ektiposi(c, 2 * n);
            }
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
                b = NULL;
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
