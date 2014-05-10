// remove
#include<stdio.h>
#include<stdlib.h>

#define ROW 0
#define COL 1
#define BOX 2

void printType(char type) {
	if(type == ROW ) {printf("row");}
	if(type == COL ) {printf("col");}
	if(type == BOX ) {printf("box");}
}

#define TRUE  (1)
#define FALSE (0)

#define DEBUG_LVL 1

/*char OrigSudoku[9][9] = { // can be solved easily without guessing
{ 0,0,0,  8,0,0,  0,0,0},
{ 3,1,2,  0,0,0,  0,0,0},
{ 9,0,0,  1,0,3,  5,0,0},

{ 0,0,0,  0,0,0,  0,3,2},
{ 1,2,0,  4,0,6,  0,5,9},
{ 8,4,0,  0,0,0,  0,0,0},

{ 0,0,7,  9,0,1,  0,0,6},
{ 0,0,0,  0,0,0,  1,2,4},
{ 0,0,0,  0,0,2,  0,0,0},
};*/

//char OrigSudoku[9][9] = {
//{0,3,5,  0,0,0,  0,0,8},
//{4,0,0,  0,0,0,  5,0,0},
//{6,0,8,  0,4,0,  9,1,0},

//{0,0,0,  7,8,0,  0,0,0},
//{0,0,7,  3,0,9,  6,0,0},
//{0,0,0,  0,6,2,  0,0,0},

//{0,2,4,  0,5,0,  1,0,6},
//{0,0,9,  0,0,0,  0,0,5},
//{1,0,0,  0,0,0,  4,7,0},
//};

/*char OrigSudoku[9][9] = { // extreme level
{2,0,0,  0,0,0,  0,3,7},
{7,0,0,  0,0,4,  0,0,0},
{0,9,1,  3,0,0,  0,0,0},

{0,2,0,  0,0,8,  0,6,0},
{5,0,0,  0,0,0,  0,0,1},
{0,7,0,  6,0,0,  0,9,0},

{0,0,0,  0,0,2,  5,7,0},
{0,0,0,  9,0,0,  0,0,8},
{9,3,0,  0,0,0,  0,0,6},
};*/

/*char OrigSudoku[9][9] = {
{0,0,0,  7,0,4,  0,2,8},
{0,4,6,  0,3,0,  0,0,0},
{0,0,0,  0,0,0,  0,0,5},

{0,5,8,  0,2,6,  0,0,0},
{0,0,0,  0,0,0,  0,0,0},
{0,0,0,  0,4,9,  5,7,0},

{2,3,0,  0,0,0,  0,0,0},
{0,0,0,  0,1,0,  3,9,0},
{4,7,0,  3,0,9,  0,0,0},
};*/

/*char OrigSudoku[9][9] = {
{4,0,0,  0,5,0,  0,0,9},
{0,3,0,  6,0,4,  0,1,0},
{0,0,1,  0,7,0,  4,0,0},

{0,6,0,  0,0,0,  0,3,0},
{7,0,9,  0,0,0,  8,0,1},
{0,8,0,  0,0,0,  0,4,0},

{0,0,8,  0,4,0,  5,0,0},
{0,1,0,  5,0,7,  0,8,0},
{5,0,0,  0,8,0,  0,0,6},
};*/

char OrigSudoku[9][9] = {
{0,0,0,  0,6,2,  9,0,0},
{0,0,3,  7,0,0,  0,2,0},
{0,2,0,  0,0,4,  0,0,7},

{0,5,0,  0,0,7,  6,0,9},
{2,0,0,  0,1,0,  0,0,8},
{3,0,6,  8,0,0,  0,5,0},

{4,0,0,  6,0,0,  0,9,0},
{0,6,0,  0,0,1,  7,0,0},
{0,0,9,  4,5,0,  0,0,0},
};


/*char OrigSudoku[9][9] = {
{0,0,8,  5,0,0,  6,0,0},
{0,0,0,  0,6,0,  3,0,0},
{3,0,9,  1,0,0,  0,0,5},

{0,0,0,  4,9,0,  7,0,0},
{8,0,0,  0,0,0,  0,0,2},
{0,0,1,  0,3,6,  0,0,0},

{6,0,0,  0,0,7,  1,0,9},
{0,0,4,  0,1,0,  0,0,0},
{0,0,7,  0,0,9,  2,0,0}
};*/


char Sudoku[9][9] = {
{0,0,0,  0,0,0,  0,0,0},
{0,0,0,  0,0,0,  0,0,0},
{0,0,0,  0,0,0,  0,0,0},

{0,0,0,  0,0,0,  0,0,0},
{0,0,0,  0,0,0,  0,0,0},
{0,0,0,  0,0,0,  0,0,0},

{0,0,0,  0,0,0,  0,0,0},
{0,0,0,  0,0,0,  0,0,0},
{0,0,0,  0,0,0,  0,0,0},
};

int Cols[9]  = {0,0,0, 0,0,0, 0,0,0};
int Rows[9]  = {0,0,0, 0,0,0, 0,0,0};
int Boxes[9] = {0,0,0, 0,0,0, 0,0,0};



struct _point {
	char x;
	char y;
};
typedef struct _point point;

point Pt(char x,char y) {
	point pt;
	pt.x = x;
	pt.y = y;
	return pt;
}

char countBits(int bits) {
	char count = 0;
	while( bits > 0 ) {
		if( bits & 1 ) { count++; }
		bits >>= 1;
	}
	return count;
}

void printSudoku(char* bitMap, char showVals) {
	char y,x, num;
	for(y=0; y<10; y++) {
		if( y % 3 == 0 ) {
			printf("+---+---+---+\n");
		}
		//Let it go up to 9 to get closing line
		if( y == 9 ) { return; }

		for(x=0; x<10; x++) {
			if(x%3 == 0) { printf("|"); }
			if(x == 9) { continue; }
			num = *bitMap++;
			if(!showVals) {
				if(num  != 0 ) {
					printf("%d", num);
				} else {
					printf(" ");
				}
			} else {
				point pt = Pt(x+1,y+1);
				if(num != 0 ) {
					printf(" ");
				} else {
					printf("%d", countBits(cellPossibBits(pt)));
				}
			}
		}
		printf("\n");
	}
}




void printPt(point pt) {
	printf("(%d,%d)", pt.x, pt.y);
}

char inline boxNum(point pt) {
	return (pt.x - 1 )/3 + (( pt.y - 1)/3)*3;
}

	/* point first(char type, char pos)
	 * 	Returns first point in number pos group 'type'
	 * 	e.g. first(COL, 3) returns point (3,1)
	 */
point first(char type, char pos) {
	point pt;
	if( type == ROW ) {
		pt.x = 1;
		pt.y = pos;
	} else if ( type == COL ) {
		pt.x = pos;
		pt.y = 1;
	} else if ( type == BOX ) {
		pos -=1;
		pt.x = 3*(pos%3) + 1;
		pt.y = 3*(pos/3) + 1;
	}

	return pt;
}




	/* bool nextPt(point,type)
	 * Goes to next point in type
	 * Returns TRUE when complete (FALSE when not)
	 */
char nextPt(point* pt, char type) {
	if( type == ROW ) {
		if( pt->x >= 9) { 	return FALSE; }
		else {			pt->x++; return TRUE; }
	}
	if (type == COL ) {
		if( pt->y >= 9) { 	return FALSE; }
		else {			pt->y++; return TRUE; }
	}
	if (type == BOX ) {
		if ( pt->y % 3 == 0 && pt->x % 3 == 0) { return FALSE; }
		if ( pt->x % 3 == 0 ) { pt->x -= 2; pt->y += 1; return TRUE; }
		else { pt->x++; return TRUE; }
	} else {
		return FALSE;
	}

	return TRUE;
}

int inline numToBits(char num) {
	if( num == 0){ return 0; }
	else { return 1<<(num-1); }
}

	/* char bitsToNumMin(int bits, char nextNum);
	 *	Returns first value of bit greater than nextNum
	 *	Returns 0 if none.
	 */
char bitsToNumMin(int bits, char min) {
	char n = 1;
	while(bits > 0) {
		if( (bits & 1) == 1 && (n > min) ) { return n; }
		bits >>= 1;
		n++;
	}
	return 0;
}

	/* char inline bitsToNum(int bits);
	 * 	Returns first value of bits
	 * 	Returns 0 if none.
	 */
char inline bitsToNum(int bits) {
	return bitsToNumMin(bits, 0);
}

	/* int cellPossibBits(point pt);
	 * 	Returns 9 bit value of values which are not in cell's
	 * 		row, box, or column.
	 * 	Returns 0 for filled cells.
	 */
int inline cellPossibBits(point pt) {
	if (Sudoku[pt.y-1][pt.x-1] != 0) { return 0;}
	return 0x1FF ^ (Cols[pt.x-1] | Rows[pt.y-1] | Boxes[ boxNum(pt) ] );
}

	/* void insertVal(point pt, char num)
	 * 	Inserts num into sudoku grid at point pt,
	 * 		as well as into col/row/box arrays.
	 */
void insertVal(point pt, char num) {
	if( Sudoku[pt.y - 1][pt.x - 1] != 0 ) { return; }
	if( num == 0 ) { return; }
//	printf("Inserting value %d into point ", num); printPt(pt); printf("\n");

	int bits = numToBits(num);

	Rows[pt.y-1] |= bits;
	Cols[pt.x-1] |= bits;
	Boxes[boxNum(pt)] |= bits;
	Sudoku[pt.y-1][pt.x-1] = num;
}

void removeVal(point pt) {
	// complemented
	int inv_bits = 0x1FF ^ numToBits(Sudoku[pt.y-1][pt.x-1]);
	Sudoku[pt.y-1][pt.x-1] = 0;

	Rows[pt.y-1] &= inv_bits;
	Cols[pt.x-1] &= inv_bits;
	Boxes[boxNum(pt)] &= inv_bits;
}

// TODO remove ... only for debugging
// for human readable purposes
void printVals(int bits) {
    printf("0x%x: ", bits); printf("[");
	char i=9;
	int mask = 0x100;

	while( mask > 0 ) {
		if ( (bits & mask) != 0 ) { printf("%d ", i);}
		mask >>= 1;
		i--;
	}
	printf("\b]");
}

int checkExclPossib(char type, char num) {
	int bits, redundantBits, cellBits;

	char x_lim1, x_lim2;
	char y_lim1, y_lim2;

	point pt;

	redundantBits = 0;
	bits = 0;

	pt = first(type, num);
    do {
		if(Sudoku[pt.y-1][pt.x-1] != 0) { // cell not empty
			redundantBits |=  numToBits(Sudoku[pt.y-1][pt.x-1]);
		} else { // cell empty
			cellBits = cellPossibBits(pt);

			// Values which were here before AND now
			// are occuring more than once
			redundantBits |= cellBits & bits;
			bits |= cellBits;
		}
	} while ( nextPt(&pt, type) );
	// Return values which occured at least once,
	// but not more: (takes values not in redundant bits)
	return bits & (0x1FF ^ redundantBits);
}

	/* point findBitInType(bit,type,pos)
	 *	Returns the point of the first occurence of
	 *	any number in input 'bit' in group 'type', at 'pos'
	 *		e.g.: findBitInType(0b1000, COL, 3)
	 *			finds first occurence of 4 in
	 *			column 3
	 *	NOTE: returns first NUMBER not a bit
	 *	Intended to be used with 'checkExclPossib()'
	 */
point findBitInType(int bits, char type, char pos) {
	char n;
	if( bits == 0 ) { return Pt(0,0); }
	point pt = first(type, pos);

	do {
		if( (cellPossibBits(pt) & bits) != 0 ) {
			return pt;
		}
	} while ( nextPt(&pt, type) );
	return Pt(0,0);
}

char sudokuComplete(void) {
	char i;
	int bits;
	bits = 0x1FF;
	for(i=0; i<9; i++) {
		bits &= Rows[i];
	}
	return (bits & 0x1FF) == 0x1FF;
}





struct _guess {
	int rowsOn[9];
	point pt;
	char val;
	struct _guess * parentGuess;
}; typedef struct _guess guess;

guess* CurrentGuess;

void makeGuess(point pt, char val) {
    int i, mask, row;
    guess* newGuess;
    point ptIns;
    int* rowOn;

    newGuess = malloc( sizeof(guess) );
    newGuess->parentGuess = CurrentGuess;
    CurrentGuess = newGuess;

	// Record which cells were filled before guess
	for(ptIns.y=1; ptIns.y<=9; ptIns.y++) {
	    mask = 0x1;
	    row = 0;
        for( ptIns.x=1; ptIns.x<=9; ptIns.x++) {
            if( Sudoku[ptIns.y-1][ptIns.x-1] != 0 ) {
               row |= mask;
            }
            mask <<= 1;
        }
        CurrentGuess->rowsOn[ptIns.y-1] = row;
    }

	// Record guess (so next possibility can be tried later if
	// guess doesn't work out)
	CurrentGuess->pt = pt;
	CurrentGuess->val = val;

	// Guess is put into grid
	insertVal(pt, val);

}

	/* point findFewestPossib(void);
	 *	Returns the first value with only 2 possibilities,
	 *		or the overall minimum.
	 *	If no possibilities are found, Pt(0,0) is returned.
	 */
point findFewestPossib(void) {
	point pt, minPt;
	char min, temp;
	min = 10;
	minPt = Pt(0,0);
	for(pt.y=1; pt.y<10; pt.y++) {
		for(pt.x=1; pt.x<10; pt.x++) {
			temp = countBits( cellPossibBits(pt) );
			if( temp == 2 ) { return pt; }
			if( temp != 0 && temp < min ) {
				min = temp;
				minPt = pt;
			}
		}
	}
	return minPt;
}

char inline cmpPt(point a, point b) {
	return a.x == b.x && a.y == b.y;
}

char inline isNull(point pt) {
	return pt.x == 0 && pt.y == 0; // though either one being zero is invalid
}

void clearGuess(void) {
	point pt;
	int mask, row;
	for(pt.y=1; pt.y<10; pt.y++) {
		mask = 0x1;
		row = CurrentGuess->rowsOn[pt.y-1];
		for(pt.x=1; pt.x<10; pt.x++) {
			if( (row & mask) == 0 ) {
				removeVal(pt);
            }
			mask <<= 1;
		}
	}
}


void inline init() {
	CurrentGuess = 0;
}

void inline prevGuess() {
	CurrentGuess = CurrentGuess->parentGuess;
}

    /* char nextValidGuess()
     * Increments global variable CurrentGuess to next possibility,
     * popping to higher levels if necessary.
     * Returns TRUE if successful, FALSE if at root guess.
     */
char nextValidGuess() {

    guess* tmpGuess;
    int bits;

    if(CurrentGuess == 0) { return FALSE; }
    clearGuess();
    bits = cellPossibBits(CurrentGuess->pt);
    CurrentGuess->val = bitsToNumMin(bits, CurrentGuess->val);
    if( CurrentGuess->val != 0) {
        if(DEBUG_LVL >= 1) {
            printf("\tNext valid guess: %d of ", CurrentGuess->val);
            printVals(bits); printf(" at ");
            printPt(CurrentGuess->pt);printf("\n");
        }
        insertVal(CurrentGuess->pt, CurrentGuess->val);
        return TRUE;
    } else {
        // Need to pop:
        if(DEBUG_LVL >= 1) {
            printf("\tPopping from guess "); printPt(CurrentGuess->pt);
            printf("\n");
        }
        tmpGuess = CurrentGuess;
        CurrentGuess = CurrentGuess->parentGuess;
        free(tmpGuess);
        return nextValidGuess();
    }

}

int main(void) {
	point pt;
	char activity, type, num, valBits;
	int exclusiveBits, bits;
	guess* tmpGuess;

    init();


	// Initialize rows/columns
	for(pt.y=1; pt.y<=9; pt.y++) {
		for(pt.x=1; pt.x<=9; pt.x++) {
			insertVal( pt, OrigSudoku[pt.y-1][pt.x-1] );
		}
	}
	        	    printSudoku(Sudoku, FALSE);



	activity = TRUE;
	while(activity) {
		activity = FALSE;
		// Check for columns with only one possibility
		for(pt.y=1; pt.y<=9; pt.y++) {
			for(pt.x=1; pt.x<=9; pt.x++) {
				bits = cellPossibBits(pt);
				if( countBits(bits) == 1) {
					if(DEBUG_LVL >=4) {
                        printf("Determined cell ");
                        printPt(pt);
                        printf(" can only be ");
                        printVals(bits);
                        printf("\n");
					}

					insertVal(pt, bitsToNum(bits));
					activity = TRUE;
				}
			}
		}
//		break;
		if( sudokuComplete() ) { break; }
		// Keep doing the easy part until can't do anymore
		// TODO is this actually more efficient?
		if(activity) { continue;}



		// Check each group for a values that can only fit in one cell

		// Check rows/cols/boxes for exclusive possibilities
		// 	(meaning only one cell in this group that can
		// 	be value X (where all are tested))
		for(type=0; type<3; type++) { // go through every type
			for(num=1; num<10; num++) {
				exclusiveBits = checkExclPossib(type, num);
				if( exclusiveBits != 0 ) {
					pt = findBitInType(exclusiveBits, type, num);
					valBits = bitsToNum(exclusiveBits & cellPossibBits(pt) );
					insertVal(pt, valBits);
					activity = TRUE;
                    if(DEBUG_LVL >= 3) {
                        printf("Determined pt ");
                        printPt(pt);
                        printf(" is only pt in ");
                        printType(type);
                        printf(" %d that can be %d.\n", num, valBits);
                        printVals(exclusiveBits); printf("\n");
                    }
				}
			}
		}

		if(activity) { continue; }
		if( sudokuComplete() ) { printf("\a\acomplete\n"); break; }



		// At this point, trivial logic can not help.
		// Resorting to guessing:
	    pt = findFewestPossib(); // returns point with fewest possibilities

                                 // or first with only 2. If finds none, returns
                                 // null point (0,0).
        if( !isNull(pt) ) { // is not null, carry on with guess
            bits = cellPossibBits(pt);
            valBits = bitsToNum(bits);
            if(DEBUG_LVL >= 1) {
                printf("Resorting to guessing val %d ", valBits);
                printf("of possib: "); printVals(bits); printf(" for pt ");printPt(pt); printf("\n");
            }


            makeGuess(pt, valBits);
            activity = TRUE;
        } else {
            // if pt is null, no fillable empty cells remain.
            // This means either sudoku complete, or current guess is invalid.
            if( sudokuComplete() ) { printf("\a\acomplete\n"); break; }

            // At this point, the current guess must be bad.
            // nextValidGuess goes to next possibility, or to parent guess until
            // possibility found. Returns no possibilities remain at all (i.e. at root).
            activity = nextValidGuess();
            if(!activity) {
                printf("\aINVALID SUDOKU\n");
                return 1;
            }
        }

	}

	printSudoku(Sudoku, FALSE);


	return 0;
}
