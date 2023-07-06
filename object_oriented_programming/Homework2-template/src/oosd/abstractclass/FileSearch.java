package oosd.abstractclass;

import java.io.File;

public abstract class FileSearch {
  public abstract SearchResult searchForFile(File root, String queryText, int max);
}
