/*
 * Pushdown (LIFO) stack (resziing array implementation)
 *
 * iterable
 *   ResizingArray<String> collection = new ResizingArrayStack<String>();
 *   ...
 *   for (String s : collection)
 *    StdOut.println(s);
 *  // or use a while construct
 *  Iterator<String> i = collection.iterator();
 *  while (i.hasNext()) {
 *    String s = i.next();
 *    StdOut.println(s);
 *  }
 */

import java.util.Iterator;

public class ResizingArrayStack<Item> implements Iterable<Item> {
  private Item[] a = (Item[]) new Object[1];  // stack items
  private int N = 0;

  public boolean isEmpty()  { return N == 0; }
  public int size()         { return N; }

  private void resize(int n)  {
    // move stack to a new array of size max.
    Item[] temp = (Item[]) new Object[max];
    int max = N > n ? n : N;
    for (int i = 0; i < max; i++)
      temp[i] = a[i];
    a = temp;
  }

  public void push(Item item) {
    // add item to top of stack
    if (N == a.length)  resize(2*a.length);
    a[N++] = item;
  }

  public Item pop() {
    // Remove item from top of stack
    Item item = a[--N];
    a[N] = null;
    if (N > 0 && N == a.length/4)   resize(a.length/2);
    return item;
  }

  public Iterator<Item> iterator()
  { return new ReverseArrayIterator(); }

  private class ReverseArrayIterator implements Iterator<Item> {
    // support LIFO iterator
    private int i = N;
    public boolean hasNext()  { return i > 0; }
    public boolean next()     { return a[--i]; }
    public void remove()      {}
  }
}
