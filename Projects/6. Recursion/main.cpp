#include <stdio.h>
#include <stdlib.h>
#include "MazeParams.h"
#include "Recursion.h"


int maze[MATRIX_SIZE][MATRIX_SIZE];
#define WALL (1 << 30)
#define MARK (1 << 29)
#define MASK (((-1) ^ WALL) ^ MARK)
int start_col; // the starting column for the maze;

void printMaze(void) {
	unsigned r, c;
	for (r = 0; r < MATRIX_SIZE; r += 1) {
		for (c = 0; c < MATRIX_SIZE; c += 1) {
			switch (maze[r][c] ) {
			case 0:
				putchar(' ');
				break;
			case 1:	
				putchar('#');
				break;
			case 2: // bread crumb
				putchar('o');
				break;
			default: // error!
				putchar('@');
				break;			
			}
		}
		putchar('\n');
	}
}
 	
void printCodedMaze(void) {
	unsigned r, c;
	for (r = 0; r < MATRIX_SIZE; r += 1) {
		for (c = 0; c < MATRIX_SIZE; c += 1) {
			switch(maze[r][c] & WALL) {
			case WALL: 
				putchar('#');
				break;
			case 0:
				putchar(' ');
				break;
			}
		}
		putchar('\n');
	}
}

enum Directions {
	UP,
	DOWN, 
	LEFT,
	RIGHT
};

void interpretDir(int* prow, int* pcol, int dir) {
	switch (dir) {
		case UP: *prow = *prow - 1; break;
		case DOWN: *prow = *prow + 1; break;
		case LEFT: *pcol = *pcol - 1; break;
		case RIGHT: *pcol = *pcol + 1; break;
	}
}

void clearWall(int row, int col, int dir) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	interpretDir(&r, &c, dir);
	maze[r][c] &= ~WALL;
}

void markCell(int row, int col) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	
	maze[r][c] |= MARK;
}

int isMarked(int row, int col) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	
	return (maze[r][c] & MARK);
}


/*
 * return an integer that uniquely identifies each cell
 */
int cellID(int row, int col) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	return r * MATRIX_SIZE + c;
}

/*
 * reverse the cellID to compute the row and col numbers
 */
void findCell(int cell, int* prow, int* pcol) {
	int r = cell / MATRIX_SIZE;
	int c = cell % MATRIX_SIZE;
	*prow = r / 2;
	*pcol = c / 2;
}

/*
 * store some annotation information in a cell 
 * (the annotation must be an int less than 25 bits (i.e., smaller than 32 million)
 */
void annotateCell(int row, int col, int annotation) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	
	maze[r][c] &= ~MASK;
	maze[r][c] |= annotation;
}

int annotation(int row, int col) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	
	return maze[r][c] & MASK;
}

void clearCellMark(int row, int col) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	
	maze[r][c] &= ~MARK;
}

void clearCell(int row, int col) {
	int r = row * 2 + 1;
	int c = col * 2 + 1;
	
	maze[r][c] = 0;
}

void makeAllWalls(void) {
	unsigned r, c;
	unsigned row, col;
	for (r = 0; r < MATRIX_SIZE; r += 1) {
		for (c = 0; c < MATRIX_SIZE; c += 1) {
			maze[r][c] = WALL;
		}
	}
	for (row = 0; row < MAZE_SIZE; row += 1) {
		for (col = 0; col < MAZE_SIZE; col += 1) {
			clearCell(row, col);
		}
	}
}

/*
 * this function makes a random maze with exactly one path between
 * any two points in the maze
 *
 * If you're curious about the algorithm, come talk to me.  It's not very
 * complicated (although the code might be confusing)
 */
void makeMaze() {
	int num_visited = 1;
	int first;
	int finish_col;
	makeAllWalls();
	markCell(0, 0);  // mark the first cell as visited
	
	/* add the first cell (row 0, col 0) to the linked list of visited cells */
	first = cellID(0, 0);
	annotateCell(0, 0, 0);
	
	while(num_visited < MAZE_SIZE * MAZE_SIZE) {
		int visit = rand() % num_visited;
		int cell = first; 
		int row, col;
		int d;
		int nrow, ncol;

		findCell(cell, &row, &col);
		while (visit > 0) {
			cell = annotation(row, col);
			findCell(cell, &row, &col);
			visit -= 1;
		}
		d = rand() % 4;
		nrow = row; // row of neighbor cell
		ncol = col; // col of neighbor cell
		interpretDir(&nrow, &ncol, d);
		if (nrow >= 0 && nrow < MAZE_SIZE
			&& ncol >= 0 && ncol < MAZE_SIZE
			&& !isMarked(nrow, ncol)) {
			clearWall(row, col, d);
			num_visited += 1;
			markCell(nrow, ncol);
			annotateCell(nrow, ncol, first);
			first = cellID(nrow, ncol);	
		}
	}
	
	start_col = rand() % MAZE_SIZE;
	start_col = 2 * start_col + 1;
	maze[0][start_col] &= ~WALL;
	finish_col = rand() % MAZE_SIZE;
	maze[MATRIX_SIZE - 1][2 * finish_col + 1] &= ~WALL;
}


/*
 * recode the maze so that all walls are exactly 1 and all 
 * other cells are exactly zero
 */
void recodeMaze(void) {
	int r, c;
	for (r = 0; r < MATRIX_SIZE; r += 1) {
		for (c = 0; c < MATRIX_SIZE; c += 1) {
			maze[r][c] = ((maze[r][c] & WALL) == WALL);
		}
	}
}
	

int main(void) {
	int magic_number = 130000;

	/* test min */
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	printf("the smallest of the first 10 natural numbers is: %d\n", minIt(a, 10));
	printf("the smallest of the first 10 natural numbers is: %d\n", minRec1(a, 10));
	printf("the smallest of the first 10 natural numbers is: %d\n", minRec2(a, 10));
	a[3] = -1;
	printf("now the smallest is %d\n", minIt(a, 10));
	printf("now the smallest is %d\n", minRec1(a, 10));
	printf("now the smallest is %d\n", minRec2(a, 10));
	
    printf("TESTING RECURSIVE MIN FUNCTION\n");
    printf("Generating sets of 50 elements with random numbers from [A, B] where A and B are random numbers in range [0, 1000) and B > A\n");
    printf("50 test cases total\n\n");

    int a00[] = {317, 557, 460, 287, 365, 360, 314, 242, 324, 396, 399, 490, 283, 185, 442, 308, 182, 559, 280, 514, 399, 437, 522, 251, 182, 181, 573, 335, 240, 580, 426, 377, 388, 228, 378, 515, 189, 323, 220, 277, 248, 290, 444, 204, 190, 168, 543, 484, 473, 247};
    int actualMin00 = 168;
    int minA00 = minRec1(a00, 50);
    int minB00 = minRec2(a00, 50);
    printf("TEST CASE 00\n");
    printf("minRec1.....%s!\n", (actualMin00 == minA00 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin00 == minB00 ? "PASSED" : "FAILED"));
    printf("\n");

    int a01[] = {605, 690, 652, 641, 734, 736, 774, 629, 652, 672, 709, 733, 710, 634, 652, 739, 659, 703, 658, 758, 799, 736, 757, 675, 608, 670, 806, 643, 677, 693, 782, 769, 642, 638, 774, 733, 776, 805, 760, 777, 732, 775, 627, 713, 711, 701, 723, 790, 717, 652};
    int actualMin01 = 605;
    int minA01 = minRec1(a01, 50);
    int minB01 = minRec2(a01, 50);
    printf("TEST CASE 01\n");
    printf("minRec1.....%s!\n", (actualMin01 == minA01 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin01 == minB01 ? "PASSED" : "FAILED"));
    printf("\n");

    int a02[] = {458, 590, 823, 867, 464, 722, 738, 523, 886, 695, 516, 529, 778, 790, 508, 857, 784, 732, 689, 498, 660, 573, 883, 586, 819, 521, 641, 734, 697, 446, 741, 615, 780, 834, 614, 515, 716, 488, 448, 868, 476, 688, 703, 614, 635, 719, 751, 855, 842, 740};
    int actualMin02 = 446;
    int minA02 = minRec1(a02, 50);
    int minB02 = minRec2(a02, 50);
    printf("TEST CASE 02\n");
    printf("minRec1.....%s!\n", (actualMin02 == minA02 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin02 == minB02 ? "PASSED" : "FAILED"));
    printf("\n");

    int a03[] = {512, 191, 518, 527, 481, 281, 448, 573, 362, 323, 276, 483, 298, 263, 562, 588, 566, 217, 512, 547, 448, 235, 199, 479, 502, 370, 527, 269, 508, 383, 224, 394, 280, 209, 575, 519, 529, 423, 464, 494, 394, 458, 467, 269, 423, 322, 254, 221, 440, 266};
    int actualMin03 = 191;
    int minA03 = minRec1(a03, 50);
    int minB03 = minRec2(a03, 50);
    printf("TEST CASE 03\n");
    printf("minRec1.....%s!\n", (actualMin03 == minA03 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin03 == minB03 ? "PASSED" : "FAILED"));
    printf("\n");

    int a04[] = {423, 554, 328, 524, 525, 99, 640, 332, 449, 148, 152, 256, 75, 93, 80, 368, 354, 406, 337, 648, 446, 188, 624, 106, 669, 363, 285, 577, 294, 337, 615, 432, 358, 69, 560, 637, 191, 531, 587, 448, 508, 413, 87, 84, 464, 128, 357, 470, 62, 617};
    int actualMin04 = 62;
    int minA04 = minRec1(a04, 50);
    int minB04 = minRec2(a04, 50);
    printf("TEST CASE 04\n");
    printf("minRec1.....%s!\n", (actualMin04 == minA04 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin04 == minB04 ? "PASSED" : "FAILED"));
    printf("\n");

    int a05[] = {876, 905, 821, 885, 822, 866, 908, 864, 852, 898, 913, 856, 889, 899, 879, 874, 869, 903, 871, 859, 852, 896, 825, 860, 859, 861, 844, 906, 897, 911, 901, 873, 861, 826, 867, 821, 848, 850, 876, 891, 823, 888, 860, 882, 882, 867, 817, 902, 880, 884};
    int actualMin05 = 817;
    int minA05 = minRec1(a05, 50);
    int minB05 = minRec2(a05, 50);
    printf("TEST CASE 05\n");
    printf("minRec1.....%s!\n", (actualMin05 == minA05 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin05 == minB05 ? "PASSED" : "FAILED"));
    printf("\n");

    int a06[] = {565, 248, 441, 207, 638, 629, 237, 294, 200, 326, 599, 166, 186, 121, 604, 441, 528, 176, 508, 305, 618, 437, 179, 139, 405, 179, 569, 338, 526, 340, 165, 92, 398, 637, 43, 141, 205, 175, 44, 296, 362, 489, 285, 529, 331, 599, 170, 489, 355, 207};
    int actualMin06 = 43;
    int minA06 = minRec1(a06, 50);
    int minB06 = minRec2(a06, 50);
    printf("TEST CASE 06\n");
    printf("minRec1.....%s!\n", (actualMin06 == minA06 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin06 == minB06 ? "PASSED" : "FAILED"));
    printf("\n");

    int a07[] = {729, 353, 425, 646, 641, 665, 360, 507, 444, 340, 436, 688, 391, 349, 521, 697, 500, 320, 410, 627, 337, 635, 697, 469, 634, 700, 617, 551, 329, 654, 634, 770, 695, 387, 373, 658, 630, 460, 609, 338, 504, 318, 706, 523, 461, 580, 385, 583, 344, 605};
    int actualMin07 = 318;
    int minA07 = minRec1(a07, 50);
    int minB07 = minRec2(a07, 50);
    printf("TEST CASE 07\n");
    printf("minRec1.....%s!\n", (actualMin07 == minA07 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin07 == minB07 ? "PASSED" : "FAILED"));
    printf("\n");

    int a08[] = {685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685, 685};
    int actualMin08 = 685;
    int minA08 = minRec1(a08, 50);
    int minB08 = minRec2(a08, 50);
    printf("TEST CASE 08\n");
    printf("minRec1.....%s!\n", (actualMin08 == minA08 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin08 == minB08 ? "PASSED" : "FAILED"));
    printf("\n");

    int a09[] = {391, 597, 524, 499, 410, 619, 377, 589, 357, 598, 514, 602, 518, 531, 468, 577, 352, 340, 371, 397, 434, 422, 627, 558, 383, 351, 601, 541, 389, 353, 489, 605, 456, 574, 490, 543, 447, 507, 611, 573, 548, 556, 632, 432, 563, 567, 638, 637, 483, 417};
    int actualMin09 = 340;
    int minA09 = minRec1(a09, 50);
    int minB09 = minRec2(a09, 50);
    printf("TEST CASE 09\n");
    printf("minRec1.....%s!\n", (actualMin09 == minA09 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin09 == minB09 ? "PASSED" : "FAILED"));
    printf("\n");

    int a10[] = {599, 665, 628, 635, 598, 594, 597, 644, 678, 676, 644, 650, 656, 650, 674, 635, 623, 656, 674, 674, 657, 616, 615, 644, 625, 632, 676, 647, 664, 607, 617, 641, 634, 593, 616, 598, 626, 653, 629, 657, 591, 601, 590, 597, 641, 675, 645, 674, 620, 598};
    int actualMin10 = 590;
    int minA10 = minRec1(a10, 50);
    int minB10 = minRec2(a10, 50);
    printf("TEST CASE 10\n");
    printf("minRec1.....%s!\n", (actualMin10 == minA10 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin10 == minB10 ? "PASSED" : "FAILED"));
    printf("\n");

    int a11[] = {636, 582, 687, 603, 562, 526, 488, 546, 406, 394, 536, 654, 572, 688, 399, 561, 508, 646, 613, 597, 472, 430, 694, 607, 430, 473, 681, 463, 448, 589, 497, 667, 571, 423, 531, 516, 450, 556, 427, 456, 631, 564, 587, 422, 421, 422, 407, 440, 435, 602};
    int actualMin11 = 394;
    int minA11 = minRec1(a11, 50);
    int minB11 = minRec2(a11, 50);
    printf("TEST CASE 11\n");
    printf("minRec1.....%s!\n", (actualMin11 == minA11 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin11 == minB11 ? "PASSED" : "FAILED"));
    printf("\n");

    int a12[] = {890, 917, 784, 905, 930, 813, 813, 901, 805, 801, 875, 850, 927, 834, 940, 839, 931, 873, 868, 922, 886, 914, 822, 800, 911, 910, 846, 784, 943, 806, 833, 884, 925, 854, 871, 855, 874, 859, 784, 787, 930, 849, 873, 872, 904, 940, 790, 833, 840, 935};
    int actualMin12 = 784;
    int minA12 = minRec1(a12, 50);
    int minB12 = minRec2(a12, 50);
    printf("TEST CASE 12\n");
    printf("minRec1.....%s!\n", (actualMin12 == minA12 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin12 == minB12 ? "PASSED" : "FAILED"));
    printf("\n");

    int a13[] = {747, 804, 796, 750, 799, 813, 805, 753, 784, 752, 791, 795, 769, 786, 791, 747, 785, 810, 753, 778, 759, 761, 755, 757, 750, 744, 755, 791, 786, 764, 794, 780, 773, 764, 763, 762, 795, 785, 761, 754, 774, 796, 755, 773, 768, 761, 768, 764, 763, 782};
    int actualMin13 = 744;
    int minA13 = minRec1(a13, 50);
    int minB13 = minRec2(a13, 50);
    printf("TEST CASE 13\n");
    printf("minRec1.....%s!\n", (actualMin13 == minA13 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin13 == minB13 ? "PASSED" : "FAILED"));
    printf("\n");

    int a14[] = {485, 475, 487, 488, 486, 555, 456, 474, 552, 496, 494, 525, 530, 467, 492, 442, 532, 517, 544, 476, 509, 505, 539, 508, 525, 473, 505, 498, 528, 503, 526, 489, 557, 455, 506, 544, 485, 546, 542, 473, 535, 506, 522, 545, 511, 467, 492, 530, 448, 450};
    int actualMin14 = 442;
    int minA14 = minRec1(a14, 50);
    int minB14 = minRec2(a14, 50);
    printf("TEST CASE 14\n");
    printf("minRec1.....%s!\n", (actualMin14 == minA14 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin14 == minB14 ? "PASSED" : "FAILED"));
    printf("\n");

    int a15[] = {531, 511, 497, 515, 509, 528, 513, 510, 503, 529, 528, 508, 523, 492, 517, 533, 509, 524, 508, 527, 497, 492, 517, 492, 522, 488, 534, 492, 514, 525, 521, 524, 519, 506, 502, 494, 530, 505, 520, 526, 532, 534, 510, 524, 489, 522, 523, 506, 516, 529};
    int actualMin15 = 488;
    int minA15 = minRec1(a15, 50);
    int minB15 = minRec2(a15, 50);
    printf("TEST CASE 15\n");
    printf("minRec1.....%s!\n", (actualMin15 == minA15 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin15 == minB15 ? "PASSED" : "FAILED"));
    printf("\n");

    int a16[] = {697, 767, 749, 721, 731, 763, 719, 725, 821, 700, 745, 796, 750, 810, 735, 814, 752, 752, 717, 820, 709, 818, 805, 716, 747, 705, 781, 819, 744, 805, 730, 729, 773, 758, 764, 766, 749, 725, 794, 764, 804, 758, 719, 798, 815, 821, 783, 789, 769, 697};
    int actualMin16 = 697;
    int minA16 = minRec1(a16, 50);
    int minB16 = minRec2(a16, 50);
    printf("TEST CASE 16\n");
    printf("minRec1.....%s!\n", (actualMin16 == minA16 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin16 == minB16 ? "PASSED" : "FAILED"));
    printf("\n");

    int a17[] = {721, 777, 894, 879, 710, 906, 714, 837, 885, 878, 807, 712, 824, 928, 880, 752, 791, 750, 747, 811, 783, 748, 721, 766, 766, 868, 822, 847, 908, 875, 735, 866, 724, 866, 805, 896, 756, 821, 778, 723, 760, 777, 811, 914, 711, 709, 874, 907, 866, 915};
    int actualMin17 = 709;
    int minA17 = minRec1(a17, 50);
    int minB17 = minRec2(a17, 50);
    printf("TEST CASE 17\n");
    printf("minRec1.....%s!\n", (actualMin17 == minA17 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin17 == minB17 ? "PASSED" : "FAILED"));
    printf("\n");

    int a18[] = {793, 457, 569, 814, 613, 471, 413, 416, 416, 493, 516, 807, 485, 558, 488, 386, 648, 520, 803, 739, 514, 700, 445, 572, 674, 583, 672, 760, 489, 651, 652, 548, 792, 653, 703, 501, 765, 549, 487, 440, 482, 430, 633, 721, 495, 570, 727, 687, 665, 656};
    int actualMin18 = 386;
    int minA18 = minRec1(a18, 50);
    int minB18 = minRec2(a18, 50);
    printf("TEST CASE 18\n");
    printf("minRec1.....%s!\n", (actualMin18 == minA18 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin18 == minB18 ? "PASSED" : "FAILED"));
    printf("\n");

    int a19[] = {561, 299, 723, 335, 312, 497, 186, 821, 697, 748, 212, 608, 618, 217, 630, 430, 711, 818, 496, 507, 220, 182, 573, 692, 240, 754, 717, 800, 289, 838, 548, 626, 374, 301, 383, 340, 415, 194, 460, 613, 833, 315, 619, 710, 536, 658, 267, 638, 747, 671};
    int actualMin19 = 182;
    int minA19 = minRec1(a19, 50);
    int minB19 = minRec2(a19, 50);
    printf("TEST CASE 19\n");
    printf("minRec1.....%s!\n", (actualMin19 == minA19 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin19 == minB19 ? "PASSED" : "FAILED"));
    printf("\n");

    int a20[] = {40, 41, 37, 39, 40, 36, 40, 35, 33, 41, 36, 40, 35, 36, 42, 33, 42, 33, 41, 33, 38, 35, 40, 38, 37, 40, 41, 38, 41, 39, 34, 42, 40, 34, 40, 33, 39, 33, 40, 33, 38, 36, 40, 42, 40, 35, 33, 38, 41, 36};
    int actualMin20 = 33;
    int minA20 = minRec1(a20, 50);
    int minB20 = minRec2(a20, 50);
    printf("TEST CASE 20\n");
    printf("minRec1.....%s!\n", (actualMin20 == minA20 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin20 == minB20 ? "PASSED" : "FAILED"));
    printf("\n");

    int a21[] = {757, 629, 463, 663, 371, 479, 768, 616, 332, 625, 328, 526, 364, 507, 680, 782, 459, 698, 544, 523, 556, 742, 736, 763, 316, 669, 487, 778, 661, 334, 414, 371, 723, 461, 545, 507, 314, 612, 526, 476, 689, 415, 581, 715, 588, 409, 509, 335, 710, 396};
    int actualMin21 = 314;
    int minA21 = minRec1(a21, 50);
    int minB21 = minRec2(a21, 50);
    printf("TEST CASE 21\n");
    printf("minRec1.....%s!\n", (actualMin21 == minA21 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin21 == minB21 ? "PASSED" : "FAILED"));
    printf("\n");

    int a22[] = {819, 420, 663, 737, 869, 968, 672, 470, 712, 850, 628, 255, 497, 606, 784, 554, 483, 484, 714, 813, 602, 889, 638, 678, 561, 845, 922, 619, 717, 450, 250, 506, 680, 245, 237, 631, 556, 856, 914, 650, 620, 589, 840, 921, 897, 934, 835, 560, 939, 317};
    int actualMin22 = 237;
    int minA22 = minRec1(a22, 50);
    int minB22 = minRec2(a22, 50);
    printf("TEST CASE 22\n");
    printf("minRec1.....%s!\n", (actualMin22 == minA22 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin22 == minB22 ? "PASSED" : "FAILED"));
    printf("\n");

    int a23[] = {253, 676, 620, 647, 387, 243, 789, 392, 274, 402, 679, 906, 666, 775, 836, 779, 235, 881, 562, 558, 475, 729, 630, 924, 832, 222, 635, 733, 265, 238, 240, 463, 342, 638, 909, 255, 394, 788, 709, 273, 552, 711, 838, 429, 980, 799, 798, 717, 865, 710};
    int actualMin23 = 222;
    int minA23 = minRec1(a23, 50);
    int minB23 = minRec2(a23, 50);
    printf("TEST CASE 23\n");
    printf("minRec1.....%s!\n", (actualMin23 == minA23 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin23 == minB23 ? "PASSED" : "FAILED"));
    printf("\n");

    int a24[] = {549, 612, 773, 747, 779, 799, 681, 908, 689, 527, 416, 809, 504, 664, 605, 449, 800, 877, 520, 465, 796, 603, 836, 554, 555, 853, 779, 477, 558, 572, 945, 914, 579, 845, 466, 540, 786, 445, 486, 601, 831, 474, 731, 424, 457, 446, 866, 554, 494, 771};
    int actualMin24 = 416;
    int minA24 = minRec1(a24, 50);
    int minB24 = minRec2(a24, 50);
    printf("TEST CASE 24\n");
    printf("minRec1.....%s!\n", (actualMin24 == minA24 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin24 == minB24 ? "PASSED" : "FAILED"));
    printf("\n");

    int a25[] = {760, 836, 851, 735, 761, 622, 515, 612, 622, 764, 667, 821, 639, 652, 599, 624, 837, 526, 588, 816, 609, 632, 584, 752, 599, 846, 594, 789, 727, 775, 705, 751, 642, 731, 594, 720, 689, 778, 657, 607, 821, 511, 724, 586, 530, 582, 697, 821, 839, 664};
    int actualMin25 = 511;
    int minA25 = minRec1(a25, 50);
    int minB25 = minRec2(a25, 50);
    printf("TEST CASE 25\n");
    printf("minRec1.....%s!\n", (actualMin25 == minA25 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin25 == minB25 ? "PASSED" : "FAILED"));
    printf("\n");

    int a26[] = {344, 845, 907, 979, 887, 426, 806, 383, 628, 974, 523, 431, 734, 179, 143, 772, 274, 346, 436, 243, 782, 328, 440, 893, 107, 518, 606, 561, 824, 715, 118, 372, 705, 748, 529, 493, 808, 723, 452, 821, 120, 149, 346, 817, 248, 949, 958, 331, 337, 630};
    int actualMin26 = 107;
    int minA26 = minRec1(a26, 50);
    int minB26 = minRec2(a26, 50);
    printf("TEST CASE 26\n");
    printf("minRec1.....%s!\n", (actualMin26 == minA26 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin26 == minB26 ? "PASSED" : "FAILED"));
    printf("\n");

    int a27[] = {574, 421, 675, 387, 582, 539, 600, 170, 506, 496, 529, 125, 695, 142, 435, 203, 127, 181, 372, 636, 261, 634, 370, 70, 200, 520, 229, 327, 487, 61, 322, 142, 518, 111, 158, 369, 600, 584, 635, 135, 343, 323, 521, 618, 164, 563, 361, 476, 401, 544};
    int actualMin27 = 61;
    int minA27 = minRec1(a27, 50);
    int minB27 = minRec2(a27, 50);
    printf("TEST CASE 27\n");
    printf("minRec1.....%s!\n", (actualMin27 == minA27 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin27 == minB27 ? "PASSED" : "FAILED"));
    printf("\n");

    int a28[] = {476, 534, 524, 482, 515, 553, 470, 483, 535, 559, 436, 433, 417, 535, 533, 515, 428, 494, 509, 441, 536, 464, 399, 490, 503, 418, 549, 429, 549, 513, 556, 550, 548, 431, 458, 392, 523, 422, 544, 414, 508, 430, 561, 521, 529, 429, 418, 551, 438, 457};
    int actualMin28 = 392;
    int minA28 = minRec1(a28, 50);
    int minB28 = minRec2(a28, 50);
    printf("TEST CASE 28\n");
    printf("minRec1.....%s!\n", (actualMin28 == minA28 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin28 == minB28 ? "PASSED" : "FAILED"));
    printf("\n");

    int a29[] = {521, 444, 674, 511, 675, 450, 772, 471, 410, 710, 357, 649, 311, 716, 696, 664, 628, 727, 577, 399, 374, 605, 342, 607, 436, 537, 547, 312, 581, 640, 382, 395, 332, 649, 736, 555, 564, 478, 452, 532, 746, 572, 685, 529, 639, 763, 328, 725, 765, 617};
    int actualMin29 = 311;
    int minA29 = minRec1(a29, 50);
    int minB29 = minRec2(a29, 50);
    printf("TEST CASE 29\n");
    printf("minRec1.....%s!\n", (actualMin29 == minA29 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin29 == minB29 ? "PASSED" : "FAILED"));
    printf("\n");

    int a30[] = {605, 574, 633, 632, 556, 495, 637, 526, 575, 488, 623, 507, 608, 551, 552, 521, 486, 534, 612, 498, 539, 529, 599, 509, 488, 594, 550, 595, 543, 593, 542, 495, 628, 618, 545, 600, 634, 570, 616, 557, 528, 537, 572, 627, 487, 629, 614, 509, 490, 561};
    int actualMin30 = 486;
    int minA30 = minRec1(a30, 50);
    int minB30 = minRec2(a30, 50);
    printf("TEST CASE 30\n");
    printf("minRec1.....%s!\n", (actualMin30 == minA30 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin30 == minB30 ? "PASSED" : "FAILED"));
    printf("\n");

    int a31[] = {440, 439, 742, 469, 550, 653, 485, 721, 498, 430, 821, 505, 858, 829, 852, 565, 868, 350, 808, 799, 412, 638, 518, 631, 564, 587, 436, 749, 528, 363, 566, 694, 735, 361, 519, 833, 585, 778, 373, 792, 512, 412, 510, 508, 464, 711, 709, 383, 744, 630};
    int actualMin31 = 350;
    int minA31 = minRec1(a31, 50);
    int minB31 = minRec2(a31, 50);
    printf("TEST CASE 31\n");
    printf("minRec1.....%s!\n", (actualMin31 == minA31 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin31 == minB31 ? "PASSED" : "FAILED"));
    printf("\n");

    int a32[] = {454, 463, 363, 462, 453, 394, 574, 567, 485, 538, 410, 477, 379, 550, 468, 531, 489, 508, 532, 429, 473, 377, 534, 575, 587, 422, 578, 581, 428, 458, 470, 508, 558, 427, 413, 367, 464, 532, 360, 511, 502, 512, 361, 475, 438, 528, 549, 540, 452, 453};
    int actualMin32 = 360;
    int minA32 = minRec1(a32, 50);
    int minB32 = minRec2(a32, 50);
    printf("TEST CASE 32\n");
    printf("minRec1.....%s!\n", (actualMin32 == minA32 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin32 == minB32 ? "PASSED" : "FAILED"));
    printf("\n");

    int a33[] = {377, 542, 774, 487, 314, 269, 761, 471, 286, 696, 545, 413, 764, 574, 473, 276, 762, 766, 401, 516, 296, 665, 739, 832, 736, 574, 550, 859, 644, 700, 613, 458, 279, 496, 789, 292, 619, 755, 578, 540, 268, 252, 758, 794, 324, 765, 437, 528, 261, 247};
    int actualMin33 = 247;
    int minA33 = minRec1(a33, 50);
    int minB33 = minRec2(a33, 50);
    printf("TEST CASE 33\n");
    printf("minRec1.....%s!\n", (actualMin33 == minA33 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin33 == minB33 ? "PASSED" : "FAILED"));
    printf("\n");

    int a34[] = {676, 611, 572, 536, 617, 570, 647, 621, 610, 613, 649, 658, 654, 599, 634, 587, 622, 529, 624, 502, 667, 637, 569, 664, 671, 646, 535, 505, 626, 568, 521, 623, 568, 574, 634, 517, 657, 597, 664, 599, 625, 568, 560, 535, 659, 643, 566, 526, 664, 649};
    int actualMin34 = 502;
    int minA34 = minRec1(a34, 50);
    int minB34 = minRec2(a34, 50);
    printf("TEST CASE 34\n");
    printf("minRec1.....%s!\n", (actualMin34 == minA34 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin34 == minB34 ? "PASSED" : "FAILED"));
    printf("\n");

    int a35[] = {616, 715, 802, 408, 317, 776, 813, 536, 471, 509, 705, 605, 535, 380, 307, 420, 424, 344, 587, 428, 609, 707, 352, 656, 480, 698, 651, 432, 755, 245, 490, 456, 301, 833, 608, 671, 764, 558, 490, 301, 681, 417, 750, 783, 276, 316, 799, 469, 399, 767};
    int actualMin35 = 245;
    int minA35 = minRec1(a35, 50);
    int minB35 = minRec2(a35, 50);
    printf("TEST CASE 35\n");
    printf("minRec1.....%s!\n", (actualMin35 == minA35 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin35 == minB35 ? "PASSED" : "FAILED"));
    printf("\n");

    int a36[] = {913, 866, 927, 868, 930, 865, 872, 877, 870, 866, 891, 927, 898, 866, 932, 867, 868, 930, 925, 920, 921, 862, 867, 901, 865, 889, 880, 904, 904, 928, 888, 932, 929, 903, 928, 873, 886, 884, 925, 879, 863, 868, 868, 935, 883, 882, 919, 911, 867, 917};
    int actualMin36 = 862;
    int minA36 = minRec1(a36, 50);
    int minB36 = minRec2(a36, 50);
    printf("TEST CASE 36\n");
    printf("minRec1.....%s!\n", (actualMin36 == minA36 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin36 == minB36 ? "PASSED" : "FAILED"));
    printf("\n");

    int a37[] = {718, 674, 746, 712, 679, 734, 635, 734, 711, 721, 680, 637, 645, 731, 653, 648, 730, 652, 709, 650, 703, 735, 704, 710, 689, 719, 695, 631, 683, 662, 693, 741, 631, 738, 699, 705, 678, 743, 739, 636, 704, 680, 624, 716, 691, 696, 698, 709, 726, 627};
    int actualMin37 = 624;
    int minA37 = minRec1(a37, 50);
    int minB37 = minRec2(a37, 50);
    printf("TEST CASE 37\n");
    printf("minRec1.....%s!\n", (actualMin37 == minA37 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin37 == minB37 ? "PASSED" : "FAILED"));
    printf("\n");

    int a38[] = {645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645};
    int actualMin38 = 645;
    int minA38 = minRec1(a38, 50);
    int minB38 = minRec2(a38, 50);
    printf("TEST CASE 38\n");
    printf("minRec1.....%s!\n", (actualMin38 == minA38 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin38 == minB38 ? "PASSED" : "FAILED"));
    printf("\n");

    int a39[] = {491, 540, 482, 474, 512, 537, 475, 586, 563, 512, 441, 519, 592, 465, 479, 428, 550, 482, 544, 560, 595, 447, 512, 552, 492, 487, 526, 446, 594, 543, 512, 423, 452, 499, 441, 591, 445, 584, 540, 471, 509, 440, 506, 471, 571, 537, 550, 437, 478, 479};
    int actualMin39 = 423;
    int minA39 = minRec1(a39, 50);
    int minB39 = minRec2(a39, 50);
    printf("TEST CASE 39\n");
    printf("minRec1.....%s!\n", (actualMin39 == minA39 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin39 == minB39 ? "PASSED" : "FAILED"));
    printf("\n");

    int a40[] = {286, 132, 661, 198, 121, 658, 169, 410, 244, 588, 154, 676, 271, 692, 465, 510, 452, 628, 599, 179, 441, 703, 655, 636, 678, 176, 424, 490, 184, 533, 503, 322, 380, 402, 556, 398, 322, 511, 540, 483, 403, 705, 160, 444, 222, 152, 646, 555, 453, 314};
    int actualMin40 = 121;
    int minA40 = minRec1(a40, 50);
    int minB40 = minRec2(a40, 50);
    printf("TEST CASE 40\n");
    printf("minRec1.....%s!\n", (actualMin40 == minA40 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin40 == minB40 ? "PASSED" : "FAILED"));
    printf("\n");

    int a41[] = {778, 839, 708, 736, 760, 704, 797, 792, 670, 771, 745, 739, 642, 769, 842, 755, 632, 735, 700, 666, 658, 794, 737, 822, 638, 709, 754, 667, 716, 687, 631, 699, 816, 651, 804, 736, 816, 827, 659, 627, 687, 716, 852, 649, 709, 785, 773, 662, 650, 758};
    int actualMin41 = 627;
    int minA41 = minRec1(a41, 50);
    int minB41 = minRec2(a41, 50);
    printf("TEST CASE 41\n");
    printf("minRec1.....%s!\n", (actualMin41 == minA41 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin41 == minB41 ? "PASSED" : "FAILED"));
    printf("\n");

    int a42[] = {443, 210, 217, 110, 602, 518, 126, 555, 187, 284, 536, 293, 552, 203, 375, 555, 378, 505, 403, 477, 135, 521, 195, 468, 685, 108, 116, 578, 507, 248, 574, 450, 520, 307, 237, 203, 132, 530, 650, 379, 486, 467, 395, 202, 269, 329, 652, 107, 539, 155};
    int actualMin42 = 107;
    int minA42 = minRec1(a42, 50);
    int minB42 = minRec2(a42, 50);
    printf("TEST CASE 42\n");
    printf("minRec1.....%s!\n", (actualMin42 == minA42 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin42 == minB42 ? "PASSED" : "FAILED"));
    printf("\n");

    int a43[] = {238, 540, 459, 307, 431, 553, 279, 538, 448, 614, 36, 198, 469, 556, 551, 183, 189, 510, 402, 304, 206, 365, 275, 360, 424, 127, 100, 436, 564, 448, 183, 521, 536, 125, 40, 576, 199, 543, 586, 197, 313, 106, 579, 594, 568, 134, 213, 178, 460, 60};
    int actualMin43 = 36;
    int minA43 = minRec1(a43, 50);
    int minB43 = minRec2(a43, 50);
    printf("TEST CASE 43\n");
    printf("minRec1.....%s!\n", (actualMin43 == minA43 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin43 == minB43 ? "PASSED" : "FAILED"));
    printf("\n");

    int a44[] = {869, 816, 791, 797, 834, 741, 782, 897, 781, 816, 780, 787, 864, 803, 836, 800, 804, 793, 840, 805, 905, 863, 800, 735, 869, 800, 867, 816, 768, 789, 791, 761, 903, 780, 897, 801, 844, 831, 789, 748, 736, 897, 805, 792, 800, 844, 782, 810, 892, 884};
    int actualMin44 = 735;
    int minA44 = minRec1(a44, 50);
    int minB44 = minRec2(a44, 50);
    printf("TEST CASE 44\n");
    printf("minRec1.....%s!\n", (actualMin44 == minA44 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin44 == minB44 ? "PASSED" : "FAILED"));
    printf("\n");

    int a45[] = {475, 418, 606, 314, 311, 343, 559, 609, 593, 377, 450, 465, 478, 587, 483, 446, 341, 606, 545, 597, 416, 323, 315, 518, 504, 296, 573, 292, 611, 293, 290, 335, 303, 539, 362, 431, 619, 541, 530, 417, 573, 420, 564, 506, 361, 595, 530, 582, 316, 471};
    int actualMin45 = 290;
    int minA45 = minRec1(a45, 50);
    int minB45 = minRec2(a45, 50);
    printf("TEST CASE 45\n");
    printf("minRec1.....%s!\n", (actualMin45 == minA45 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin45 == minB45 ? "PASSED" : "FAILED"));
    printf("\n");

    int a46[] = {384, 525, 418, 489, 613, 353, 293, 317, 303, 695, 702, 621, 434, 515, 351, 296, 275, 596, 671, 692, 396, 257, 545, 586, 234, 523, 339, 329, 412, 477, 301, 479, 531, 510, 542, 679, 378, 517, 597, 470, 552, 629, 280, 596, 365, 382, 387, 401, 493, 296};
    int actualMin46 = 234;
    int minA46 = minRec1(a46, 50);
    int minB46 = minRec2(a46, 50);
    printf("TEST CASE 46\n");
    printf("minRec1.....%s!\n", (actualMin46 == minA46 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin46 == minB46 ? "PASSED" : "FAILED"));
    printf("\n");

    int a47[] = {465, 640, 402, 471, 388, 538, 601, 487, 384, 417, 512, 496, 561, 462, 535, 513, 647, 600, 571, 562, 525, 410, 360, 486, 600, 542, 439, 600, 456, 636, 600, 388, 623, 603, 434, 578, 556, 439, 662, 611, 600, 365, 642, 492, 570, 556, 489, 360, 421, 563};
    int actualMin47 = 360;
    int minA47 = minRec1(a47, 50);
    int minB47 = minRec2(a47, 50);
    printf("TEST CASE 47\n");
    printf("minRec1.....%s!\n", (actualMin47 == minA47 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin47 == minB47 ? "PASSED" : "FAILED"));
    printf("\n");

    int a48[] = {393, 455, 372, 492, 450, 461, 501, 400, 392, 464, 346, 448, 412, 387, 510, 453, 359, 344, 464, 458, 494, 402, 354, 336, 324, 447, 400, 350, 344, 390, 497, 452, 467, 360, 491, 500, 372, 519, 438, 325, 393, 350, 483, 321, 477, 369, 394, 362, 428, 410};
    int actualMin48 = 321;
    int minA48 = minRec1(a48, 50);
    int minB48 = minRec2(a48, 50);
    printf("TEST CASE 48\n");
    printf("minRec1.....%s!\n", (actualMin48 == minA48 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin48 == minB48 ? "PASSED" : "FAILED"));
    printf("\n");

    int a49[] = {441, 620, 308, 324, 861, 484, 337, 939, 713, 322, 736, 416, 365, 341, 704, 496, 479, 628, 622, 262, 471, 819, 850, 564, 730, 719, 250, 658, 823, 560, 776, 353, 390, 811, 431, 769, 922, 556, 784, 760, 717, 543, 941, 517, 845, 699, 753, 804, 744, 636};
    int actualMin49 = 250;
    int minA49 = minRec1(a49, 50);
    int minB49 = minRec2(a49, 50);
    printf("TEST CASE 49\n");
    printf("minRec1.....%s!\n", (actualMin49 == minA49 ? "PASSED" : "FAILED"));
    printf("minRec2.....%s!\n", (actualMin49 == minB49 ? "PASSED" : "FAILED"));
    printf("\n");

    printf("\n\n");
    printf("TESTING RECURSIVE CHANGE FUNCTION\n");
    printf("50 test cases total\n\n");

	/* test sqrt */
	printf("the sqrt of 25 is %.15f\n", sqrtIt(25.0, 0, 25.0));
	printf("the sqrt of 26 is %.15f\n", sqrtIt(26.0, 0, 26.0));
	printf("the sqrt of 2 is %.15f\n", sqrtIt(2.0, 0, 2.0));
	printf("the sqrt of 25 is %.15f\n", sqrtRec(25.0, 0, 25.0));
	printf("the sqrt of 26 is %.15f\n", sqrtRec(26.0, 0, 26.0));
	printf("the sqrt of 2 is %.15f\n", sqrtRec(2.0, 0, 2.0));
	printf("the sqrt of 3 is %.15f\n", sqrtRec(3.0, 0, 3.0));
	printf("the sqrt of 8 is %.15f\n", sqrtRec(8.0, 0, 8.0));
	printf("the sqrt of 1 is %.15f\n", sqrtRec(1.0, 0, 1.0));
	printf("the sqrt of 20 is %.15f\n", sqrtRec(20.0, 0, 20.0));
	printf("the sqrt of 63 is %.15f\n", sqrtRec(63.0, 0, 63.0));
	printf("the sqrt of 64 is %.15f\n", sqrtRec(64.0, 0, 64.0));
	printf("the sqrt of 69 is %.15f\n", sqrtRec(69.0, 0, 69.0));
	printf("the sqrt of 100 is %.15f\n", sqrtRec(100.0, 0, 100.0));
	printf("the sqrt of 1500 is %.15f\n", sqrtRec(1500.0, 0, 1500.0));
	printf("the sqrt of 0.5 is %.15f\n", sqrtRec(0.5, 0, 1));
	printf("the sqrt of 0 is %.15f\n", sqrtRec(0, 0, 1));
	printf("the sqrt of 140000 is %.15f\n", sqrtRec(140000.0, 0, 140000.0));
	printf("the sqrt of 1 is %.15f\n", sqrtRec(1.0, 0, 1.0));


	/* test strCompare */
	char* s1; char* s2;
	s1 = "apple"; s2 = "apricot";
	if (strCompare(s1, s2) < 0) { 
		printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
	}
			
	s1 = "Apple"; s2 = "apple";
	if (strCompare(s1, s2) < 0) { 
		printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
	}

	s1 = "baby boy"; s2 = "banana";
	if (strCompare(s1, s2) < 0) { 
		printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
	}

	s1 = "a rather silly string"; s2 = "a rather silly string";
	if (strCompare(s1, s2) == 0) { 
		printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
	}

	s1 = "12345"; s2 = "12345";
	if (strCompare(s1, s2) == 0) { 
		printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
	}

	s1 = "Numbers: 12345"; s2 = "12345";
	if (strCompare(s1, s2) > 0) { 
		printf("\"%s\" is greater than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be greater than \"%s\"\n", s1, s2);
	}

	s1 = "Texas"; s2 = "California";
	if (strCompare(s1, s2) > 0) { 
		printf("\"%s\" is greater than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be greater than \"%s\"\n", s1, s2);
	}


    s1 = "Hello"; s2 = "hello";
	if (strCompare(s1, s2) < 0) { 
		printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
	}

	s1 = ""; s2 = "";
	if (strCompare(s1, s2) == 0) { 
		printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
	}

	s1 = "2"; s2 = "1";
	if (strCompare(s1, s2) > 0) { 
		printf("\"%s\" is greater than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be greater than \"%s\"\n", s1, s2);
	}

	/* test strCompare2 */
	s1 = "apple"; s2 = "Apricot";
	if (strCompare2(s1, s2) < 0) { 
		printf("\"%s\" is less than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be less than \"%s\"\n", s1, s2);
	}

	s1 = "Batman!"; s2 = "bat man";
	if (strCompare2(s1, s2) == 0) { 
		printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
	}

	s1 = "OMG, WTF?"; s2 = "oh my goodness, what the heck?";
	if (strCompare2(s1, s2) > 0) { 
		printf("\"%s\" is greater than \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be greater than \"%s\"\n", s1, s2);
	}
	
	s1 = ""; s2 = "";
	if (strCompare2(s1, s2) == 0) { 
		printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
	}

	s1 = "!@#$^&*"; s2 = ")(*&^$#@";
	if (strCompare2(s1, s2) == 0) { 
		printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
	}

	s1 = "123456789"; s2 = "87654321234567890";
	if (strCompare2(s1, s2) == 0) { 
		printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
	}

	s1 = "PENIS"; s2 = "penis";
	if (strCompare2(s1, s2) == 0) { 
		printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
	}

	s1 = "ApPLe"; s2 = "apple";
	if (strCompare2(s1, s2) == 0) { 
		printf("\"%s\" is equal to \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be equal to \"%s\"\n", s1, s2);
	}

	s1 = "abce"; s2 = "ABCD";
	if (strCompare2(s1, s2) > 0) { 
		printf("\"%s\" is greater \"%s\", very good\n", s1, s2);
	} else {
		printf("oops, \"%s\" should be greater than \"%s\"\n", s1, s2);
	}
	/* test maze */		
	srand(magic_number);
	makeMaze();
	recodeMaze();
	printf("recursive solution to the maze\n");
	solveMazeRec(0, start_col);	
	printMaze();
	printf("\n\n\n");
	
	magic_number = 1500;
	srand(magic_number);
	makeMaze();
	recodeMaze();
	printf("recursive solution to the maze\n");
	solveMazeRec(0, start_col);	
	printMaze();
	printf("\n\n\n");

	magic_number = 8;
	srand(magic_number);
	makeMaze();
	recodeMaze();
	printf("recursive solution to the maze\n");
	solveMazeRec(0, start_col);	
	printMaze();
	printf("\n\n\n");

	magic_number = 123456;
	srand(magic_number);
	makeMaze();
	recodeMaze();
	printf("recursive solution to the maze\n");
	solveMazeRec(0, start_col);	
	printMaze();
	printf("\n\n\n");

	magic_number = 13412;
	srand(magic_number);
	makeMaze();
	recodeMaze();
	printf("recursive solution to the maze\n");
	solveMazeRec(0, start_col);	
	printMaze();
	printf("\n\n\n");

	magic_number = 300;
	srand(magic_number);
	makeMaze();
	recodeMaze();
	printf("recursive solution to the maze\n");
	solveMazeRec(0, start_col);	
	printMaze();
	printf("\n\n\n");

	magic_number = 123;
	srand(magic_number);
	makeMaze();
	recodeMaze();
	printf("recursive solution to the maze\n");
	solveMazeRec(0, start_col);	
	printMaze();
	printf("\n\n\n");

	magic_number = 524367;
	srand(magic_number);
	makeMaze();
	recodeMaze();
	printf("recursive solution to the maze\n");
	solveMazeRec(0, start_col);	
	printMaze();
	printf("\n\n\n");

	magic_number = 1;
	srand(magic_number);
	makeMaze();
	recodeMaze();
	printf("recursive solution to the maze\n");
	solveMazeRec(0, start_col);	
	printMaze();
	printf("\n\n\n");

	magic_number = 8765;
	srand(magic_number);
	makeMaze();
	recodeMaze();
	printf("recursive solution to the maze\n");
	solveMazeRec(0, start_col);	
	printMaze();
	printf("\n\n\n");

	magic_number = 1234543;
	srand(magic_number);
	makeMaze();
	recodeMaze();
	printf("recursive solution to the maze\n");
	solveMazeRec(0, start_col);	
	printMaze();
	printf("\n\n\n");

	magic_number = 34;
	srand(magic_number);
	makeMaze();
	recodeMaze();
	printf("recursive solution to the maze\n");
	solveMazeRec(0, start_col);	
	printMaze();
	printf("\n\n\n");
	

	/* test Martian */
	Martian change1 = change(15);
	printf("change 1 should be 0d, 3n, 0p and is: %dd %dn %dp\n", change1.dodeks, change1.nicks, change1.pennies);

	Martian change2 = change(0);
	printf("change 2 should be 0d, 0n, 0p and is: %dd %dn %dp\n", change2.dodeks, change2.nicks, change2.pennies);

	Martian change3 = change(17);
	printf("change 3 should be 1d, 1n, 0p and is: %dd %dn %dp\n", change3.dodeks, change3.nicks, change3.pennies);

	Martian change4 = change(25);
	printf("change 4 should be 2d, 0n, 1p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);

	change4 = change(20);
	printf("change 4 should be 0d, 4n, 0p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);
	change4 = change(40);
	printf("change 4 should be 2d, 3n, 1p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);
	change4 = change(22);
	printf("change 4 should be 1d, 2n, 0p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);
	change4 = change(34);
	printf("change 4 should be 2d, 2n, 0p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);
	change4 = change(100);
	printf("change 4 should be 7d, 3n, 1p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);
	change4 = change(99);
	printf("change 4 should be 7d, 3n, 0p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);
	change4 = change(69);
	printf("change 4 should be 4d, 4n, 1p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);

	/* A very simple and obvious test of the general form of Martian
	 * be sure and test your solution more thoroughly!!!! */
	change4 = change(25, 5, 12);
	printf("change 4 should be 2d, 0n, 1p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);
	change4 = change(51, 5, 10);
	printf("change 4 should be 5d, 0n, 1p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);
	change4 = change(99, 7, 12);
	printf("change 4 should be 7d, 2n, 1p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);
	change4 = change(100, 3, 19);
	printf("change 4 should be 5d, 1n, 2p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);
	change4 = change(82, 2, 13);
	printf("change 4 should be 6d, 2n, 0p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);
	change4 = change(57, 10, 15);
	printf("change 4 should be 3d, 1n, 2p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);
	change4 = change(49, 9, 11);
	printf("change 4 should be 2d, 3n, 0p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);
	change4 = change(63, 6, 17);
	printf("change 4 should be 3d, 2n, 0p and is: %dd %dn %dp\n", change4.dodeks, change4.nicks, change4.pennies);
}