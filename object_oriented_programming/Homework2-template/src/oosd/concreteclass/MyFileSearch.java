package oosd.concreteclass;

import oosd.abstractclass.FileSearch;
import oosd.abstractclass.SearchResult;

import java.io.File;

public class MyFileSearch extends FileSearch {
    SearchResult that = new MySearchResult();
    @Override
    public SearchResult searchForFile(File root, String queryText, int max){

        if(!root.isDirectory()){
             System.out.println("Path is not a directory");
        }
        for(File folderItem : root.listFiles()){
            if(folderItem.isDirectory()){
                if(folderItem.getName().contains(queryText)){
                    that.addFile(folderItem);
                }
                searchForFile(folderItem, queryText, max);

            }
            else{
                if(folderItem.getName().contains(queryText)){
                    that.addFile(folderItem);
                }
            }
        }

        return that;
    }
}