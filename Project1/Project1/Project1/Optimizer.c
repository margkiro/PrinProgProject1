#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

void delete(Instruction *node){
	Instruction *tmp;
	tmp = node->next;
	node->next = tmp->next->next;
	Instruction *tmp2;
	tmp2 = node->next;
	tmp2->prev = node;
	tmp->next->prev = NULL;
	tmp->prev = NULL;
	tmp->next->next = NULL;
	tmp->next = NULL;
	free(tmp->next);
	free(tmp);
}

int main()
{
	Instruction *head;

	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}
	Instruction *tmp;
	tmp = head;
	while (tmp && tmp->next && tmp->next->next) {
		if(tmp->opcode == LOADI && tmp->next->opcode == LOADI){
			if(tmp->next->next->opcode == ADD){
  			int val1 = tmp->field2;
				int val2 = tmp->next->field2;
				int res = val1 + val2;
				tmp->field2 = res;
				tmp->field1 = tmp->next->next->field1;
				delete(tmp);
				tmp = head;
			}else if(tmp->next->next->opcode == SUB){
				int val1 = tmp->field2;
				int val2 = tmp->next->field2;
				int res = val1 - val2;
				tmp->field2 = res;
				tmp->field1 = tmp->next->next->field3;
				delete(tmp);
				tmp = head;
			}else if(tmp->next->next->opcode == MUL){
				int val1 = tmp->field2;
				int val2 = tmp->next->field2;
				int res = val1 * val2;
				tmp->field2 = res;
				tmp->field1 = tmp->next->next->field3;
				delete(tmp);
				tmp = head;
			}else{
				tmp = tmp->next;
			}
		}else{
			tmp = tmp->next;
		}
		/* code */
	}
	/* YOUR CODE GOES HERE */
	if (head) {
		PrintInstructionList(stdout, head);
		DestroyInstructionList(head);
	}
	return EXIT_SUCCESS;
}
