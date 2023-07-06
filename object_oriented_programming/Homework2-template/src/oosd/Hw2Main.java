package oosd;

import java.io.File;

import oosd.concreteclass.MyFileSearch;
import oosd.abstractclass.FileSearch;
import oosd.abstractclass.SearchResult;


public class Hw2Main {
  public static void main(String[] args) {
    File root = new File("C:\\Users\\sskys\\2022_ite2037_2018008040\\"); // If you are Window user, enter root of your disk drive (ex. "C://" or "D://")
    FileSearch fileSearch = new MyFileSearch();
    SearchResult searchResult = fileSearch.searchForFile(root, "specialfilenamethatshouldnotduplicate", 5);
    for (int i = 0; i < searchResult.getSize(); ++i) {
      File file = searchResult.getFiles()[i];
      if (file.isDirectory()) System.out.println(">>directory:" + file.getAbsolutePath());
      else System.out.println(">>file:" + file.getAbsolutePath());
    }
    searchResult.copy().checkFileAryReference(searchResult);
  }
}

