package oosd.concreteclass;

import oosd.abstractclass.SearchResult;

import java.io.File;

public class MySearchResult extends SearchResult {

    public MySearchResult(){
        this.size = 0;
        this.max = 5;
        this.files = new File[max];
    }
    public int getSize(){
        return this.size;
    }
    public File[] getFiles(){
        return files;
    }
    public boolean isMax(){
        return size >= max;
    }
    public void addFile(File file){
        if(!isMax()){
            files[size++] = file;
        }
    }
    public SearchResult copy(){
        SearchResult copy = new MySearchResult();
        for(int i=0;i<5;i++){
            File thatFile = new File("C:\\");
            thatFile = files[i];
            copy.getFiles()[i] = thatFile;
        }
        return copy;
    }
}