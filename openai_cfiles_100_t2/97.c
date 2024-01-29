
void initializeArray(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        arr[i] = value;
    }
}


You can use this function to initialize an array with a specific value. For example, if you have an array `myArray` of size 5 and you want to initialize it with the value 0, you can call the function like this:

c
initializeArray(myArray, 5, 0);
