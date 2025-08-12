#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_t *game, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_t *game, unsigned int snum);
static char next_square(game_t *game, unsigned int snum);
static void update_tail(game_t *game, unsigned int snum);
static void update_head(game_t *game, unsigned int snum);

/* Task 1 */
game_t *create_default_game() {
  // TODO: Implement this function.
  snake_t *snake=malloc(sizeof(snake_t));
  if (!snake)
    return NULL;

  snake->live=true;
  snake->head_col=4;
  snake->head_row=2;
  snake->tail_col=2;
  snake->tail_row=2;

  game_t *game=malloc(sizeof(game_t));
  if (!game)
  {
    free(snake);
    return NULL;
  }

  game->num_rows=18;
  game->num_snakes=1;
  game->snakes=snake;

  game->board=malloc(sizeof(char*)*game->num_rows);
  
  if (!game->board)
  {
    free(snake);
    free(game);
    return NULL;
  }

  unsigned int num_cols=20;
  for (unsigned int i=0;i<game->num_rows;i++)
  {
    game->board[i]=malloc(sizeof(char)*(num_cols+2));

    if (!game->board[i])
    {
      for (unsigned int j=0;j<i;j++)
      {
        free(game->board[j]);
      }
      free(game->board);
      free(snake);
      free(game);
      return NULL;
    }

    if (i==0 || i==game->num_rows-1)
    {
      for (unsigned int j=0;j<num_cols;j++)
      {
        game->board[i][j]='#';
      }
    }

    else
    {
      game->board[i][0]='#';

      for (unsigned int j=1;j<num_cols-1;j++)
      {
        game->board[i][j]=' ';
      }

      game->board[i][num_cols-1]='#';
    }

    game->board[i][num_cols]='\n';
    game->board[i][num_cols+1]='\0';
  }

  game->board[2][2]='d';
  game->board[2][3]='>';
  game->board[2][4]='D';

  game->board[2][9]='*';


  // return NULL;
  return game;
}

/* Task 2 */
void free_game(game_t *game) {
  // TODO: Implement this function.
  if (!game)
  {
    return;
  }

  if (game->snakes)
  {
    free(game->snakes);
  }

  if (game->board)
  {
    for (unsigned int i=0;i<game->num_rows;i++)
    {
      free(game->board[i]);
    }

    free(game->board);
  }

  if (game)
  {
    free(game);
  }


  
  return;
}

/* Task 3 */
void print_board(game_t *game, FILE *fp) {
  // TODO: Implement this function.
  if (!game || !game->board)
  {
    return;
  }

  for (unsigned int i=0;i<game->num_rows;i++)
  {
    fprintf(fp,"%s",game->board[i]);
  }

  return;
}

/*
  Saves the current game into filename. Does not modify the game object.
  (already implemented for you).
*/
void save_board(game_t *game, char *filename) {
  FILE *f = fopen(filename, "w");
  print_board(game, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_t *game, unsigned int row, unsigned int col) { return game->board[row][col]; }

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_t *game, unsigned int row, unsigned int col, char ch) {
  game->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  char* snake_tail="wasd";
  for(unsigned int i=0;i<strlen(snake_tail);i++)
  {
    if (snake_tail[i]==c)
    {
      return true;
    }
  }
  return false;
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
  char* snake_head="WASDx";
  for(unsigned int i=0;i<strlen(snake_head);i++)
  {
    if (snake_head[i]==c)
    {
      return true;
    }
  }
  return false;
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
  char* snake="wasd^<v>WASDx";
  for(unsigned int i=0;i<strlen(snake);i++)
  {
    if (snake[i]==c)
    {
      return true;
    }
  }
  return false;
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  
  // TODO: Implement this function.
  switch(c)
  {
    case '^':
      return 'w';

    case '<':
      return 'a';

    case 'v':
      return 's';

    case '>':
      return 'd';
  }
  return '?';
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  
  switch(c)
  {
    case 'W':
      return '^';

    case 'A':
      return '<';

    case 'S':
      return 'v';

    case 'D':
      return '>';
  }
  return '?';
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implement this function.
  switch(c)
  {
    case 'v':
    case 's': 
    case 'S':
      return cur_row+1;

    case '^':
    case 'w':
    case 'W':
      return cur_row-1;
  }
  return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implement this function.
  switch(c)
  {
    case '>':
    case 'd':
    case 'D':
      return cur_col+1;

    case '<':
    case 'a':
    case 'A':
      return cur_col-1;
  }
  return cur_col;
}

/*
  Task 4.2

  Helper function for update_game. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  // return '?';
  snake_t snake=game->snakes[snum];
  unsigned int head_row=snake.head_row;
  unsigned int head_col=snake.head_col;

  char snake_head_char=get_board_at(game,head_row,head_col);

  unsigned int next_row=get_next_row(head_row,snake_head_char);
  unsigned int next_col=get_next_col(head_col,snake_head_char);
  
  char next_square_char=get_board_at(game,next_row,next_col);
  
  return next_square_char;
}

/*
  Task 4.3

  Helper function for update_game. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  // return;
  snake_t snake=game->snakes[snum];
  unsigned int head_row=snake.head_row;
  unsigned int head_col=snake.head_col;

  char head_char=get_board_at(game,head_row,head_col);

  unsigned int next_row=get_next_row(head_row,head_char);
  unsigned int next_col=get_next_col(head_col,head_char);

  set_board_at(game,next_row,next_col,head_char);

  char body_char=head_to_body(head_char);

  set_board_at(game,head_row,head_col,body_char);

  game->snakes[snum].head_row=next_row;
  game->snakes[snum].head_col=next_col;
}

/*
  Task 4.4

  Helper function for update_game. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  // return;
  snake_t snake=game->snakes[snum];
  unsigned int tail_row=snake.tail_row;
  unsigned int tail_col=snake.tail_col;

  char tail_char=get_board_at(game,tail_row,tail_col);
  unsigned int next_row=get_next_row(tail_row,tail_char);
  unsigned int next_col=get_next_col(tail_col,tail_char);

  char body_char=get_board_at(game,next_row,next_col);
  char new_tail_char=body_to_tail(body_char);

  set_board_at(game,next_row,next_col,new_tail_char);

  set_board_at(game,tail_row,tail_col,' ');

  game->snakes[snum].tail_row=next_row;
  game->snakes[snum].tail_col=next_col;
}

/* Task 4.5 */
void update_game(game_t *game, int (*add_food)(game_t *game)) {
  // TODO: Implement this function.
  // return;
  for (unsigned int i=0;i<game->num_snakes;i++)
  {
    if (!game->snakes[i].live)
    {
      continue;
    }

    char next_square_char=next_square(game,i);

    if (next_square_char=='#' || is_snake(next_square_char))
    {
      game->snakes[i].live=false;
      set_board_at(game,game->snakes[i].head_row,game->snakes[i].head_col,'x');
    }

    else if(next_square_char=='*')
    {
      update_head(game,i);
      add_food(game);
    }

    else {
      update_head(game,i);
      update_tail(game,i);
    }
  }
}

/* Task 5.1 */
char *read_line(FILE *fp) {
  // TODO: Implement this function.
  // return NULL;
  // char* line=malloc(sizeof(char)*300);
  // if (line==NULL)
  // {
  //   return NULL;
  // }
  // if(fgets(line,300,fp)==NULL)
  // {
  //   free(line);
  //   return NULL;
  // }
  

  // return line;

  size_t capacity=512;
  char* line=malloc(sizeof(char)*capacity);
  if (line==NULL)
  {
    return NULL;
  }

  if (fgets(line,(int)capacity,fp)==NULL)
  {
    free(line);
    return NULL;
  }

  size_t len=strlen(line);

  while (len>0 && line[len-1]!='\n' && !feof(fp))
  {
    capacity*=2;
    char* new_line=realloc(line,capacity);

    if (new_line==NULL)
    {
      free(line);
      return NULL;
    }

    line=new_line;
    if (fgets(line+len,(int)(capacity-len),fp)==NULL)
    {
      free(line);
      return NULL;
    }
    len=strlen(line);
  }
  return line;
}

/* Task 5.2 */
game_t *load_board(FILE *fp) {
  // TODO: Implement this function.
  // return NULL;
  char **lines=NULL;
  unsigned int num_rows=0;

  char* line;
  while((line=read_line(fp))!=NULL)
  {
    num_rows++;
    char** new_lines=realloc(lines,sizeof(char*)*num_rows);

    if (new_lines==NULL)
    {
      for(int i=0;i<num_rows-1;i++)
      {
        free(lines[i]);
      }
      free(lines);
      free(line);
      return NULL;
    }
    lines=new_lines;
    lines[num_rows-1]=line;
  }

  game_t *game=malloc(sizeof(game_t));
  if(game==NULL)
  {
    for(int i=0;i<num_rows;i++)
    {
      free(lines[i]);
    }
    free(lines);
    return NULL;
  }

  game->board=lines;
  game->num_rows=num_rows;
  game->num_snakes=0;
  game->snakes=NULL;

  return game;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  // return;
  snake_t snake=game->snakes[snum];

  unsigned int tail_row=snake.tail_row;
  unsigned int tail_col=snake.tail_col;

  char current_char=get_board_at(game,tail_row,tail_col);

  while(!is_head(current_char))
  {
    unsigned int next_row=get_next_row(tail_row,current_char);
    unsigned int next_col=get_next_col(tail_col,current_char);

    current_char=get_board_at(game,next_row,next_col);
    tail_row=next_row;
    tail_col=next_col;
  }

  game->snakes[snum].head_row=tail_row;
  game->snakes[snum].head_col=tail_col;

  return;
}

/* Task 6.2 */
game_t *initialize_snakes(game_t *game) {
  // TODO: Implement this function.
  // return NULL;
  unsigned snake_count=0;
  
  for(unsigned int i=0;i<game->num_rows;i++)
  {
    for (unsigned int j=0;j<strlen(game->board[i]);j++)
    {
      if (is_tail(get_board_at(game,i,j)))
      {
        snake_count++;
      }
    }
  }

  game->num_snakes=snake_count;

  if(snake_count==0)
  {
    game->snakes=NULL;
    return game;
  }

  game->snakes=malloc(sizeof(snake_t)*snake_count);
  if(game->snakes==NULL)
  {
    return NULL;
  }

  unsigned int snake_index=0;

  for(unsigned int i=0;i<game->num_rows;i++)
  {
    for(unsigned int j=0;j<strlen(game->board[i]);j++)
    {
      if (is_tail(get_board_at(game,i,j)))
      {
        snake_t* snake=&game->snakes[snake_index];

        snake->live=true;
        snake->tail_row=i;
        snake->tail_col=j;

        find_head(game,snake_index);

        snake_index++;

        if(snake_index>=snake_count)
        {
          break;
        }
      }
    }
  }

  return game;
}
