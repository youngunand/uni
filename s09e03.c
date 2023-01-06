#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_NAME 64

typedef struct lecture_hall {
    char name[MAX_LEN_NAME + 1];
    unsigned short size;
    unsigned short num_seats;
} lecture_hall_t;

void print_lecture_hall(lecture_hall_t* lecture_hall_ptr)
{
    printf("Lecture Hall: name: %s, size: %d, seats: %d\n", lecture_hall_ptr->name, lecture_hall_ptr->size, lecture_hall_ptr->num_seats);
}

void print_all_lecture_halls(lecture_hall_t lecture_halls[]) {
    for (size_t i = 0; i < 4; i++) {
        print_lecture_hall(&(lecture_halls[i]));
    }
}

int name_comparator(const void* ptr1, const void* ptr2)
{
    lecture_hall_t* hall_ptr_1 = (lecture_hall_t*)ptr1; //cast void pinter
    lecture_hall_t* hall_ptr_2 = (lecture_hall_t*)ptr2;
    return strcmp(hall_ptr_1->name, hall_ptr_2->name); //use strcmp as suggested in man-page
}

int size_comparator(const void* ptr1, const void* ptr2)
{
    lecture_hall_t* hall_ptr_1 = (lecture_hall_t*)ptr1;
    lecture_hall_t* hall_ptr_2 = (lecture_hall_t*)ptr2;
    if (hall_ptr_1->size > hall_ptr_2->size) {
        return 1;
    } else if (hall_ptr_1->size < hall_ptr_2->size) {
        return -1;
    }
    return 0;
}

int num_seats_comparator(const void* ptr1, const void* ptr2)
{
    lecture_hall_t* hall_ptr_1 = (lecture_hall_t*)ptr1;
    lecture_hall_t* hall_ptr_2 = (lecture_hall_t*)ptr2;
    if (hall_ptr_1->num_seats > hall_ptr_2->num_seats) {
        return 1;
    } else if (hall_ptr_1->num_seats < hall_ptr_2->num_seats) {
        return -1;
    }
    return 0;
}

int lecture_hall_comparator(const void* ptr1, const void* ptr2)
{
    lecture_hall_t* hall_ptr_1 = (lecture_hall_t*)ptr1;
    lecture_hall_t* hall_ptr_2 = (lecture_hall_t*)ptr2;

    if (hall_ptr_1->num_seats == hall_ptr_2->num_seats) { //use size comparator for lecture halls with same number of seats
        return size_comparator(ptr1, ptr2);
    }
    return num_seats_comparator(ptr1, ptr2);
}

void sort_lecture_halls(lecture_hall_t* lecture_halls, const size_t num_lecture_halls, int (*comparator)(const void*, const void*))
{
    qsort(lecture_halls, num_lecture_halls, sizeof(lecture_hall_t), comparator);
}

int main()
{
    lecture_hall_t test_hall_1 = { .name = "HS2", .size = 8, .num_seats = 50 };
    lecture_hall_t test_hall_2 = { .name = "HS3", .size = 9, .num_seats = 100 };
    lecture_hall_t test_hall_3 = { .name = "HS1", .size = 10, .num_seats = 80 };
    lecture_hall_t test_hall_4 = { .name = "HS0", .size = 12, .num_seats = 180 };

    lecture_hall_t lecture_hall_array[4] = { test_hall_1, test_hall_2, test_hall_3, test_hall_4 };

    printf("unsorted array: \n");
    print_all_lecture_halls(lecture_hall_array);

    sort_lecture_halls(lecture_hall_array, 4, name_comparator);

    printf("\n sorted by name: \n");
    print_all_lecture_halls(lecture_hall_array);

    sort_lecture_halls(lecture_hall_array, 4, size_comparator);

    printf("\n sorted by size: \n");
    print_all_lecture_halls(lecture_hall_array);

    sort_lecture_halls(lecture_hall_array, 4, num_seats_comparator);

    printf("\n sorted by number of seats: \n");
    print_all_lecture_halls(lecture_hall_array);

    sort_lecture_halls(lecture_hall_array, 4, lecture_hall_comparator);

    printf("\n sorted by lecture hall: \n");
    print_all_lecture_halls(lecture_hall_array);

    return EXIT_SUCCESS;
}
