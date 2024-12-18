#include <stdio.h>
#include <string.h>
#include<stdlib.h>
typedef enum {
    A = 4,
    B = 3,
    C = 2,
    D = 1,
    F = 0,
} grade;

typedef struct {
    char mapel[30];
    grade g;
} mapel;

typedef struct {
    int id;
    char name[30];
    int subject_count;
    mapel subject[10];
} student;

student students[100];
int student_count = 0;

void getEnter();

void saveToFile(){
    FILE *f = fopen("students.txt", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // write student (id#name#subject_count#subject1#grade1#subject2#grade2#...)
    for (int i = 0; i < student_count; i++) {
        student s = students[i];
        fprintf(f, "%d#%s#%d", s.id, s.name, s.subject_count);
        for (int j = 0; j < s.subject_count; j++) {
            mapel m = s.subject[j];
            fprintf(f, "#%s#%d", m.mapel, m.g);
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

void quickSort(student students[], int low, int high) {
    if (low < high) {
        int pi = partition(students, low, high);

        quickSort(students, low, pi - 1);
        quickSort(students, pi + 1, high);
    }
}

int partition(student students[], int low, int high) {
    char *pivot = students[high].name;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (strcmp(students[j].name, pivot) < 0) {
            i++;
            student temp = students[i];
            students[i] = students[j];
            students[j] = temp;
        }
    }
    student temp = students[i + 1];
    students[i + 1] = students[high];
    students[high] = temp;

    return i + 1;
}

void insertionSort(student students[], int student_count) {
    for (int i = 1; i < student_count; i++) {
        student key = students[i];
        int j = i - 1;

        while (j >= 0 && strcmp(students[j].name, key.name) > 0) {
            students[j + 1] = students[j];
            j--;
        }
        students[j + 1] = key;
    }
}

void merge(student students[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    student L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = students[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = students[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (strcmp(L[i].name, R[j].name) <= 0) {
            students[k] = L[i];
            i++;
        } else {
            students[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        students[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        students[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(student students[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(students, left, mid);
        mergeSort(students, mid + 1, right);

        merge(students, left, mid, right);
    }
}

void selectionSort(student students[], int student_count) {
    for (int i = 0; i < student_count - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < student_count; j++) {
            if (strcmp(students[j].name, students[minIndex].name) < 0) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            student temp = students[i];
            students[i] = students[minIndex];
            students[minIndex] = temp;
        }
    }
}
int binarySearch(student students[], int student_count, int id) {
    int left = 0, right = student_count - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (students[mid].id == id) {
            return mid; 
        } else if (students[mid].id < id) {
            left = mid + 1;
            right = mid - 1;
        }
    }

    return -1;
}

int interpolationSearch(student students[], int student_count, int id) {
    int low = 0, high = student_count - 1;

    while (low <= high && id >= students[low].id && id <= students[high].id) {
        if (low == high) {
            if (students[low].id == id)
                return low;
            return -1;
        }


        int pos = low + ((id - students[low].id) * (high - low) /
                         (students[high].id - students[low].id));


        if (students[pos].id == id) {
            return pos;
        } else if (students[pos].id < id) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }

    return -1;
}






void tampilkan_mahasiswa_sorted(){
    system("cls");
    if(student_count == 0){
        printf("Belum ada mahasiswa\n");
        getEnter();

    }
    for(int i = 0; i < student_count; i++){
        for(int j = 0; j < student_count - 1 - i; j++){
            if(strcmp(students[j].name, students[j+1].name) > 0){
                student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;

            }

        }
    }

    printf("=================== List Mahasiswa Terurut Sesuai Abjad=======================\n");
    for(int i = 0; i < student_count; i++){
        printf("%s\n", students[i].name);
    }
   getEnter();
}
void delete_student() {
    int id;
    system("cls");
    printf("Masukkan NIM mahasiswa yang ingin dihapus: ");
    scanf("%d", &id); getchar();

    int found = -1;
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Mahasiswa dengan NIM %d tidak ditemukan.\n", id);
        getEnter();
        return;
    }


    for (int i = found; i < student_count - 1; i++) {
        students[i] = students[i + 1];
    }

    student_count--;
    saveToFile();

    printf("Mahasiswa dengan NIM %d berhasil dihapus.\n", id);
    getEnter();
}


void dbToMemory(){
    FILE *f = fopen("students.txt", "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }

    student_count = 0;
    while (1) {
        student s;
        int subject_count;
        int res = fscanf(f, "%d#%[^#]#%d", &s.id, s.name, &subject_count);
        if (res == EOF) {
            break;
        }

        s.subject_count = subject_count;
        for (int i = 0; i < subject_count; i++) {
            fscanf(f, "#%[^#]#%d", s.subject[i].mapel, &s.subject[i].g);
        }

        students[student_count] = s;
        student_count++;
    }

    fclose(f);
}
double hitung_gpa(student s);

void getEnter(){
    printf("Press Enter to continue...");
    while(getchar() != '\n');
}

void add_student() {
    student s;
    system("cls");
    if (student_count == 100) {
        printf("Maximum student limit reached.\n");
        getEnter();
        return;
    }

    printf("Masukkan NIM: ");
    scanf("%d", &s.id); getchar();
    printf("Masukkan Nama Mahasiswa: ");
    scanf(" %[^\n]%*c", s.name);

    s.subject_count = 0;
    students[student_count] = s;
    student_count++;

    printf("Mahasiswa berhasil ditambahkan.\n");
    saveToFile();
    getEnter();
}

void add_grade() {
    int id;
    char mapel_name[30];
    int grade_input;
    system("cls");
    printf("Masukkan NIM mahasiswa: ");
    scanf("%d", &id);getchar();


    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {

            int subject_count = 0;
            for (int j = 0; j < 10; j++) {
                if (strlen(students[i].subject[j].mapel) != 0) {
                    subject_count++;
                }
            }


            if (subject_count >= 10) {
                printf("Mahasiswa sudah memiliki 10 mata pelajaran.\n");
                getEnter();
                return;
            }

            ulang:
            system("cls");
            printf("==========================================\n");
            printf("NIM: %d\n", students[i].id);
            printf("Nama: %s\n", students[i].name);
            printf("Masukkan Mata Pelajaran: ");
            scanf(" %[^\n]", mapel_name);getchar();


            for (int k = 0; k < 10; k++) {
                if (strcmp(students[i].subject[k].mapel, mapel_name) == 0) {
                    printf("Mapel sudah ada, coba lagi.\n");
                    getEnter();
                    goto ulang;
                }
            }

            gay:
            printf("Masukkan Nilai Mahasiswa: \n 4 = A\n 3 = B\n 2 = C\n 1 = D\n 0 = F\n ex = 4\n");
            printf("Nilai: ");

            scanf("%d", &grade_input); getchar();

            if (grade_input > 4 || grade_input < 0) {
                printf("Nilai tidak valid, masukkan lagi dengan nilai yang tertera\n");
                getEnter();
                goto gay;
            }


            for (int j = 0; j < 10; j++) {
                if (strlen(students[i].subject[j].mapel) == 0) {
                    strcpy(students[i].subject[j].mapel, mapel_name);
                    students[i].subject[j].g = (grade)grade_input;
                    students[i].subject_count++;
                    printf("Mata pelajaran dan nilai berhasil ditambahkan!\n");
                    saveToFile();
                    break;
                }
            }

            printf("Apakah ingin menambahkan lagi? (y/n): ");
            char choice;
            scanf("%c", &choice); getchar();
            if (choice == 'y' || choice == 'Y') {
                goto ulang;
            }
            return;
        }
    }

    printf("NIM mahasiswa tidak ditemukan atau tidak valid.\n");
    getEnter();
}

grade distinction_grade(student s) {
    double gpa = hitung_gpa(s);

    if (gpa >= 3.5) {
        return A;
    } else if (gpa >= 2.5) {
        return B;
    } else if (gpa >= 1.5) {
        return C;
    } else if (gpa > 0.0) {
        return D;
    } else {
        return F;
    }
}


double hitung_gpa(student s) {
    if (s.subject_count == 0) {
        return 0.0;
    }

    double total = 0;
    for (int i = 0; i < s.subject_count; i++) {
        total += (double) s.subject[i].g;
    }
    return total / s.subject_count;
}

void tampilkan_mahasiswa () {
    system("cls");
    if(student_count == 0) {
        printf("Belum ada mahasiswa\n");
        getEnter();
    }
    else{
        for(int i = 0; i < student_count; i++) {
            student s = students[i];
            printf("=================Mahasiswa ke-%d===================\n\n", i+1);
            printf("NIM: %d\n", s.id);
            printf("Nama: %s\n", s.name);
            printf("GPA: %.2f\n", hitung_gpa(s));
            grade distinction = distinction_grade(s);
            printf("Distinction: ");
            switch (distinction) {
            case A: printf("A\n"); break;
            case B: printf("B\n"); break;
            case C: printf("C\n"); break;
            case D: printf("D\n"); break;
            case F: printf("F\n"); break;
            default: printf("Unknown\n");
            }
            puts("");
            printf("------------------------------------------\n");
            printf("Student grades: \n");
            for (int j = 0; j < s.subject_count; j++) {
                printf("Mata Pelajaran: %s\n", s.subject[j].mapel);
                printf("Nilai: %d\n", s.subject[j].g);
                printf("------------------------------------------\n");
            }
            puts("");
        }

    }
    getEnter();
}
int main() {
    int n;
    dbToMemory();

    do {
        system("cls");
        printf("--------Sekolah tanto --------\n");
        printf("1. Tambah Mahasiswa\n");
        printf("2. Tambah Nilai Mahasiswa\n");
        printf("3. Tampilkan Detail Mahasiswa\n");
        printf("4. Hapus Mahasiswa\n");
        printf("5. Tampilkan Mahasiswa\n");
        printf("6. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &n);getchar();

        switch (n) {
            case 1:
                add_student();
                break;
            case 2:
                add_grade();
                break;
            case 3:
                tampilkan_mahasiswa();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                tampilkan_mahasiswa_sorted();
                break;
            case 6:
                printf("Ok bye lol\n");
                break;
                return 0;
            default:
                printf("invalid, try again.\n");
                getEnter();
        }
    } while (n != 4);
    }
