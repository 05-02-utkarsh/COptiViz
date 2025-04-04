int main() {
    int x = 10;
    float y = 5.5;
    char c = 'A';

    if (x > 5) {
        x += 2;
        y = y / 2.0;
    } else {
        x = x - 1;
    }

    for (int i = 0; i < 10; i++) {
        x = x + i;
    }

    // Call function
    printValues(x, y);

    return 0;
}

// Function definition
void printValues(int a, float b) {
    printf("x = %d, y = %f\n", a, b);
}
