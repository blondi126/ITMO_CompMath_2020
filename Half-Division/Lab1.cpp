#include <iostream>
#include <math.h>

double f1(double x)   // значение функции 1 в точке x 
{
    return 2 * pow(x, 3) + pow(x, 2) - 7;
}
double f2(double x)   // значение функции 2 в точке x 
{
    return 5 * cos(3 * x) + 0.5 * x - 2;
}
double f3(double x)   // значение функции 3 в точке x 
{
    return pow(x, 5) - 2 * pow(x, 4) + 6 * pow(x, 2) + 2 * x - 4;
}
double f4(double x)   // значение функции 4 в точке x 
{
    return pow(x, 3) - 0.2 * pow(x, 2) - 0.2 * x - 1.2;
}
double f5(double x)   // значение функции5 в точке x 
{
    return log(abs(pow(x, 3)) + 1) + pow(x, 3) - 2;
}

double PolDel(double a, double b, double eps, double (*f) (double), int* c) {     // сам метод
    *c = 0;
    while (fabs(a - b) >= eps) {   // проверка на заданную точность
        if ((f(a) > 0 && f((a + b) / 2) < 0) || (f(a) < 0 && f((a + b) / 2) > 0)) {
            b = (a + b) / 2;   // корень находится в левой половине отрезка
            (*c)++;    // счетчик итераций
        }
        else
            if ((f((a + b) / 2) > 0 && f(b) < 0) || (f((a + b) / 2) < 0 && f(b) > 0)) {
                a = (a + b) / 2;   // корень находится в правой половине отрезка
                (*c)++;  // счетчик итераций
            }
            else {
                printf("Действительных корней в заданном интервале нет\n");
                break;
            }
    }
    return ((a + b) / 2);
}



int main() {
    double epsilon = 0.0000001;   // точность
    int count=0;     // счётчик итераций
    setlocale(LC_ALL, "rus");
    double (*f[5])(double);     //массив функций для удобства
    f[0] = &f1;
    f[1] = &f2;
    f[2] = &f3;
    f[3] = &f4;
    f[4] = &f5;
    double a[5] = { 1, 1, 0, 1, 1 };   // левая граница каждого корня
    double b[5] = { 2, 2, 1, 2, 2 };   // правая граница каждого корня
    double x[5];
    for (int i = 0; i < 5; i++)
        x[i] = PolDel(a[i], b[i], epsilon, f[i], &count);
    printf("Точность %.8f\n", epsilon);
    for (int i = 0; i < 5; i++) {
        printf("Корень %d уравнения на заданном промежутке: %f\nКоличество итераций: ", i + 1, x[i]);
        printf("%d\n", count);
    }

    printf("\nПроверка при точности %.7f:\n", epsilon);   
    for (int i = 0; i < 5; i++) 
        printf("f%d(x) = %.8f\n", i + 1, f[i](x[i]));     // проверка
    return 0;
}

   



