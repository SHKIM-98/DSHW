void add(char [3], char [4]);
void search(char [3]);
void delete(char [3]);

// record structure
struct record {
  char name[3];
  char number[4];
  struct record * next;
};

void print_name(struct record *);
void print_number(struct record *);
void print_data(char *, int);
void print_list();

void init_pool();



