void show_bytes(char* msg, unsigned char* ptr, int how_many) {
  printf("%s\n", msg);
  int i;
  for (i = 0; i < how_many; i++) printf(" %.2x", ptr[i]);
  printf("\n");
}
