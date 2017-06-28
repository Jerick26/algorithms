// recursive version
Node MergeLists(Node list1, Node list2) {
  if (list1 == null) return list2;
  if (list2 == null) return list1;

  if (list1.data < list2.data) {
    list1.next = MergeLists(list1.next, list2);
    return list1;
  } else {
    list2.next = MergeLists(list2.next, list1);
    return list2;
  }
}

// iterative version
Node MergeLists(Node list1, Node list2) {
  if (list1 == null) return list2;
  if (list2 == null) return list1;

  Node head;
  if (list1.data < list2.data) {
    head = list1;
  } else {
    head = list2;
    list2 = list1;
    list1 = head;
  }
  while(list1.next != null) {
    if (list1.next.data > list2.data) {
      Node tmp = list1.next;
      list1.next = list2;
      list2 = tmp;
    }
    list1 = list1.next;
  } 
  if (list1.next == null) list1.next = list2;
  return head;
}
