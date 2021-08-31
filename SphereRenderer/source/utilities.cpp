float * mulArray(float arr[], float coeff){
	for (int i = 0; i < (sizeof(arr)/sizeof(float)); i++)
	{
		arr[i] *= coeff;
	}
	return arr;
}