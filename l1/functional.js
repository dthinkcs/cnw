function map(arr, func) {
    const newArr = [];
    for (let i = 0; i < arr.length; i++) {
        newArr.push(func(arr[i]));
    }
    return newArr;
}

newArr = [1, 2, 3, 4, 5, 6]
