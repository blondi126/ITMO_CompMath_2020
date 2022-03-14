#include <iostream>
#include <math.h>

double f1(double x)   // значение функции 1 в точке x 
{
    return (2 * log10(x) - cos(x));
}

double f2(double x)   // значение функции 2 в точке x 
{
    return (2 * pow(x, 3) - 5 * pow(x, 2) - 1);
}

double f3(double x)   // значение функции 3 в точке x 
{
    return (2 * pow(sin(2 * x), 3) - cos(x));
}

double f4(double x)   // значение функции 4 в точке x 
{
    return (pow(x, 5) - 3 * pow(x, 4) + 8 * pow(x, 2) + 2 * x - 7);
}

double f5(double x)   // значение функции5 в точке x 
{
    return (0.5 * pow(x, 2) + 5 * cos(2 * x) - 2);
}

double diff(double x, double f(double x))   // первая проивзодная функции в точке x 
{
    const double h = 1e-10;
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

double diff2(double x, double (*f)(double))  // вторая производная функции в точке x
{
    const double h = 1e-10;
    return (f(x + h) - 2.0 * f(x) + f(x - h)) / (h * h);
}


double Newton(double a, double b, double eps, double (*f) (double), int* c) {     // сам метод
    *c = 1;   // счетчик итераций
    double x0, xn=0;
    if (f(a) * f(b) > 0) // если знаки функции на краях отрезка одинаковые, то здесь нет корня
       printf("Нет корней на данном отрезке\n");
    else {
        if (f(a) * diff2(a, f) > 0)  x0 = a;    // начальное приближение
        else x0 = b;
        xn = x0 - f(x0) / diff(x0, f);
        while (fabs(x0 - xn) > eps) {  // пока не достигнем необходимой точности
            x0 = xn;
            xn = x0 - f(x0) / diff(x0, f);   // формула Ньютона
            (*c)++;
        } 
        return xn;
    }
    return 0;
}



int main() {
    double epsilon = 0.001;   // точность
    int count = 0;     // счётчик итераций
    setlocale(LC_ALL, "rus");
    double (*f[5])(double);     //массив функций для удобства
    f[0] = &f1;
    f[1] = &f2;
    f[2] = &f3;
    f[3] = &f4;
    f[4] = &f5;
    double a[5] = { 1, 2, 0, 0, 0 };   // левая граница каждого корня
    double b[5] = { 2, 3, 1, 1, 1 };   // правая граница каждого корня
    double x[5];  // искомый корень
    for (int i = 0; i < 5; i++)
        x[i] = Newton(a[i], b[i], epsilon, f[i], &count);
    printf("Точность %.4f\n", epsilon);
    for (int i = 0; i < 5; i++) {
        printf("Корень %d уравнения на заданном промежутке: %f\nКоличество итераций: ", i + 1, x[i]);
        printf("%d\n", count);
    }

    printf("\nПроверка при точности %.4f:\n", epsilon);
    for (int i = 0; i < 5; i++)
        printf("f%d(x) = %.14f\n", i + 1, f[i](x[i]));     // проверка 
    return 0; 
}


