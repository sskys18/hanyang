package oosd.abstractclass;

import java.io.File;
import java.util.Arrays;

public abstract class SearchResult {
  protected File[] files;
  protected int size;
  protected int max;

  public abstract int getSize();
  public abstract File[] getFiles();
  public abstract boolean isMax();
  public abstract void addFile(File file);
  public abstract SearchResult copy();

  public void checkFileAryReference(SearchResult that) {
    if (this.files == that.getFiles()) throw new RuntimeException("Should never happen");
    if (!Arrays.equals(this.files, that.files)) throw new RuntimeException("Should never happen");
    for (int i = 0; i < size; ++i) {
      if (this.files[i] == that.getFiles()[i]) {
        throw new RuntimeException("Should never happen");
      }
    }
  }
}
