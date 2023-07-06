package Week12;

public class BinarySearch {
    private int [] array;
    private int start;
    private int end;
    public int search(int[] array, int start, int end, int x){
        int middle = 0;
        if(start <= end){
            middle = (start+end) / 2;
            if(array[middle] == x){
                return middle;
            }
            if(array[middle] > x){
                return search(array, start, middle-1, x);
            }
            if(array[middle] < x){
                return  search(array, middle+1, end, x);
            }
            return 0;
        }
        return middle;
    }

}
