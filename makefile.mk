# a.out: dyntable_client.o dynamic_table2.o
# 	gcc dyntable_client.o dynamic_table2.o
# dyntable_client.o: dyntable_client.c dyntable_impl.h
# 	gcc -c dyntable_client.c
# dynamic_table2.o: dynamic_table2.c dyntable_impl.h
# 	gcc -c dynamic_table2.c