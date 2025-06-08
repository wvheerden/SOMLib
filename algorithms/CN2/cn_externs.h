/*  File:     cn_externs.h
    Author:   Robin Boswell
    Purpose:  externs for CN

    Change Log:

      2/16/96 - Rick Kufrin, NCSA/UIUC <rkufrin@ncsa.uiuc.edu>
        Changed declaration of remove() to remove_item() (see heap.c)
*/ 

       /* SccsId = "@(#)cn_externs.h 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989" */

#include "cn_header.h"
#include "input.h"

/* create.c  */
extern Star new_star();
extern Star initial_star();
extern Node *new_node();
extern Rank *new_rank();
extern Selector *new_selector();
extern Discriminant *new_discriminant();
Quotquae *classify_examples();
extern int free_node();
extern int free_node_not_exs();
extern double **new_cn_scores();
extern int nodecounter;


/* ckrl_gen.c */

extern int ckrl_mode();
extern int root_name();
extern int print_ckrl_nominal();
/* extern int ckrl_ae2();
extern int ckrl_tree2(); */

/* ckrl_rules.c */

extern int ckrl_rules_header();
extern int ckrl_print_rules();
extern int ckrl_rules_footer();


/* attribute.c */
extern Attribute *new_attribute();
extern void free_attribute();
/* extern Attribute *nth_attribute(); */
extern char *nth_attribute_name(); 
extern char *att_val_string();
extern char *val_string();
extern List remove_attribute();
extern BOOL over_used();
extern BOOL remaining_values();
extern void setup_attribute_array();
extern Attribute **attribute_array;


/* att_order.c */
extern BOOL initialise_order_array();
extern BOOL transform_order_array();
extern BOOL insert_order_array();
extern BOOL p_member();
extern int p_length();

/* example.c */
extern BOOLEAN terminal();
extern void really_free_elist();
extern EList new_elistelement();
extern EList new_ecopy();
extern void free_elist();
extern void free_thing();

/* cn_print_thing.c */
extern void print_star();
extern void print_node();
extern void print_rank();
extern void print_quotquaeoth();
extern BOOL print_selector();
extern BOOL trivial_selector();
extern void print_rule_list();
extern void print_quots();
extern void print_greeting();
extern void print_distribution();
extern void print_rule_file();
extern void print_rule_parameters();
extern void print_cn_scores();
extern void print_i_scores();


/* main.c */
extern pqueue *HEAP_PTR;
extern RuleParams global_rule_parameters;
extern char *global_readfile;

/* specialise.c */
extern BOOL equal_selector();

/* execute.c */
extern double **execute();
extern BOOL ordered_whoosh();
extern BOOL unordered_whoosh();
extern BOOL general_whoosh();
extern void x_filter();
extern BOOL evaluate_rules();
extern void execute_rules();
extern void execute_individual();
extern int x_covered();
extern double default_acc();

/* cn.c */
extern List ordered_cn();
extern List unordered_cn();
extern BOOL empty_array();
extern List global_rule_list;
extern double   *global_distribution;
extern double    global_number_of_examples;
extern Node     *global_best_node;
extern int majority_class();
extern BOOL filter_discrete_examples();
extern int star_size;
extern float threshold;
extern int current_class;


/* print_gen_thing.c */
extern void print_el();
extern void print_elist();
extern void print_values();
extern void print_value();
extern void print_input_type();
extern void print_attribute_list();
extern void print_attval_list();
extern void print_attribute_values();
extern void print_attribute();
extern void print_attribute_bin_action();


/* interact.c */
extern int interact();
extern void cn_help();
extern InputType input_type;
extern DataFlow data_flow;
extern char data_dir[BUFSIZ];
extern float threshold;
extern BOOL tty_ok;
FILE *get_permitted_file();

/* interact_utils.c */
extern BOOL get_filename();
extern void set_signal_handling();
extern void tidy_before_quitting();
extern void scrap_till_next_command();
extern void scrap_till_newline();
extern char select_char();
extern FILE *pager_open();
extern int pager_close();
extern int maybe_print();


/* list.c */
extern List new_listelement();
extern Object *new_object();
extern List last();
extern void free_list();
extern void free_object();



/* "names.c" */
extern Attribute **attribute;
extern Atom *intern();
extern Atom *string_to_atom();
extern Attribute *string_to_attribute();
extern void hash_init();
extern Attribute *new_attribute();
extern Atom *attr_name();
extern SHORT attr_no();
extern BOOL value_id();
extern Atom *id_value();


/* test.c  */
extern int test();


/* quickfit.c */
extern void *qfalloc();
extern void qffree();
extern void qfstats();


/* peccles.c */
extern BOOL evaluate_rank();
extern BOOL significant_p();
extern BOOL integerp();
extern double dist_eval_rank();


/* heap.c */
extern void free_heap();
extern int toss_onto_heap();
extern pqueue *create_heap();
extern Node *remove_item();


/* trace.c */
extern unsigned short trace_flag;
extern unsigned short algorithm_flag;
extern unsigned short max_class_flag;
extern Ranking errest_flag;
extern void change_tracing();
extern void change_threshold();
extern void change_starsize();
extern void change_algorithm();
extern void change_errest();
extern BOOL ishelp();


/* debug.c */
extern void *raballoc();

/* rule_reader.c */

extern List value_list, *value_ptr;
extern List *rule_ptr;
extern Rule *current_rule;

void init_rule_reader();
extern void rule_par_nread();
extern void rule_par_fread();
extern void rule_par_sread();

extern void add_att_val();
extern void add_rule();
extern void init_value_list();
