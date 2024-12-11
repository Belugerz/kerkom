#include <stdio.h>
#include <string.h>

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

double hitung_gpa(student s) {
    if (s.subject_count == 0) {
        return 0.0;
    }

    double total = 0;
    for (int i = 0; i < s.subject_count; i++) {
        total += (double) s.subject[i].g;  // Ensure grade is treated as a double
    }
    return total / s.subject_count;
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

void add_student() {
    student s;
    if (student_count == 100) {
        printf("Maximum student limit reached.\n");
        return;
    }

    printf("Masukkan NIM: ");
    scanf("%d", &s.id);
    printf("Masukkan Nama Mahasiswa: ");
    scanf(" %[^\n]%*c", s.name);

    s.subject_count = 0;
    students[student_count] = s;
    student_count++;

    printf("Mahasiswa berhasil ditambahkan.\n");
}

void add_grade() {
    int id;
    char mapel_name[30];
    int grade_input;

    printf("Masukkan NIM mahasiswa: ");
    scanf("%d", &id);

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
                return;
            }

        ulang:
            printf("Masukkan Mata Pelajaran: ");
            scanf(" %[^\n]%*c", mapel_name);

            for (int k = 0; k < 10; k++) {
                if (strcmp(students[i].subject[k].mapel, mapel_name) == 0) {
                    printf("Mapel sudah ada, coba lagi.\n");
                    goto ulang;
                }
            }

        gay:
            printf("Masukkan Nilai Mahasiswa: \n 4 = A\n 3 = B\n 2 = C\n 1 = D\n 0 = F\n");
            printf("Nilai: ");
            scanf("%d", &grade_input);

            if (grade_input > 4 || grade_input < 0) {
                printf("Nilai tidak valid, masukkan lagi dengan nilai yang tertera\n");
                goto gay;
            }

            for (int j = 0; j < 10; j++) {
                if (strlen(students[i].subject[j].mapel) == 0) {
                    strcpy(students[i].subject[j].mapel, mapel_name);
                    students[i].subject[j].g = (grade)grade_input;
                    printf("Mata pelajaran dan nilai berhasil ditambahkan!\n");
                    break;
                }
            }

            printf("Apakah ingin menambahkan lagi? (y/n): ");
            char choice;
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                goto ulang;
            }

            return;
        }
    }

    printf("NIM mahasiswa tidak ditemukan atau tidak valid.\n");
}

void tampilkan_mahasiswa() {
    if (student_count == 0) {
        printf("Belum ada mahasiswa\n");
    } else {
        for (int i = 0; i < student_count; i++) {
            student s = students[i];
            printf("==========================================\n");
            printf("NIM: %d\n", s.id);
            printf("Nama: %s\n", s.name);
            printf("GPA: %.2f\n", hitung_gpa(s));

            // Get distinction grade
            grade distinction = distinction_grade(s);
            printf("Distinction Grade: ");
            switch (distinction) {
                case A: printf("A\n"); break;
                case B: printf("B\n"); break;
                case C: printf("C\n"); break;
                case D: printf("D\n"); break;
                case F: printf("F\n"); break;
                default: printf("Unknown\n");
            }

            printf("------------------------------------------\n");
            printf("Student grades: \n");
            for (int j = 0; j < s.subject_count; j++) {
                printf("Mata Pelajaran: %s\n", s.subject[j].mapel);
                printf("Nilai: %d\n", s.subject[j].g);
            }
        }
    }
}

int main() {
    int n;

    do {
        printf("--------Sekolah Tanto --------\n");
        printf("1. Tambah Mahasiswa\n");
        printf("2. Tambah Nilai Mahasiswa\n");
        printf("3. Tampilkan Mahasiswa\n");
        printf("4. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &n);

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
                printf("Ok bye lol\n");
                break;
            default:
                printf("Invalid, try again.\n");
        }
    } while (n != 4);

    return 0;
}
