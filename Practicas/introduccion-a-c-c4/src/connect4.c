#include <stdlib.h>
#include <stdio.h>
#include "connect4.h"
#include <assert.h>
#include <string.h>

void 
connect4_init (connect4* game, int rows, int columns, int num_of_players, int win_size) 
{
  game->tablero = (int **)malloc(rows * sizeof(int*));
  int k; for (k = 0; k < rows; ++k)
  {
    game->tablero[k] = (int *)malloc(columns * sizeof(int));
  }

  game->rows = rows;
  game->columns = columns;
  game->num_of_players = num_of_players;
  game->win_size = win_size;

  int i; for (i = 0; i < rows; ++i)
  {
    int j; for (j = 0; j < columns; ++j)
    {
      game->tablero[i][j] = 0;
    }
  }
}

void
connect4_free (connect4* game)
{
    int i = 0; for (i =0; i < game->rows; i++)
    {
        free(game->tablero[i]);
    }
    free(game->tablero);
}

char* 
connect4_to_string (connect4* game)
{
  char* str = malloc(sizeof(char) * 100);
  char salto = '\n';
  int num;
  char numero;

  int i; for (i = 0; i < game->rows; ++i)
  {
    int j; for (j = 0; j < game->columns; ++j)
    {
      num = game->tablero[i][j];
      numero = num + '0';
      strncat(str,&numero,1);
      if ((game->columns) == (game->rows))
      {
        if (j == (game->rows)-1 && i != (game->columns)-1)
        {
          strncat(str,&salto,1);
        }
      }
      else if ((game->columns) > (game->rows))
      {
        if (j == (game->rows)+((game->columns)-(game->rows)-1) && i != (game->columns)-((game->columns)-(game->rows)+1))
        {
          strncat(str,&salto,1);
        }
      }
      else
      {
        if (j == (game->rows)-((game->rows)-(game->columns)+1) && i != (game->columns)+((game->rows)-(game->columns)+-1))
        {
          strncat(str,&salto,1);
        }
      }
    }
  }
  return str;
}

int 
connect4_make_play (connect4* game, int player, int column)
{
  if (column < 0 || column+1 > game->columns)
  {
    return INVALID_COLUMN;
  }
  else if (player > game->num_of_players || player <= 0)
  {
    return INVALID_PLAYER;
  }
  else if (game->tablero[0][column] == 1 || game->tablero[0][column] == 2 || game->tablero[0][column] == 3)
  {
    return FULL_COLUMN;
  }
  else
  {
    if (game->tablero[(game->rows)-1][column] == 0)
    {
      game->tablero[(game->rows)-1][column] = player; return (game->rows)-((game->rows)-1+1);
    }
    else if (game->tablero[(game->rows)-2][column] == 0)
    {
      game->tablero[(game->rows)-2][column] = player; return (game->rows)-((game->rows)-2+1);
    }
    else if (game->tablero[(game->rows)-3][column] == 0)
    {
      game->tablero[(game->rows)-3][column] = player; return (game->rows)-((game->rows)-3+1);
    }
    else if (game->tablero[(game->rows)-4][column] == 0)
    {
      game->tablero[(game->rows)-4][column] = player; return (game->rows)-((game->rows)-4+1);
    }
    else if (game->tablero[(game->rows)-5][column] == 0)
    {
      game->tablero[(game->rows)-5][column] = player; return (game->rows)-((game->rows)-5+1);
    }
    else if (game->tablero[(game->rows)-6][column] == 0)
    {
      game->tablero[(game->rows)-6][column] = player; return (game->rows)-((game->rows)-6+1);
    }
  }
  return 0;
}

bool 
connect4_player_won (connect4* game, int player, int row, int column) 
{
  int cont = 0;
  int con = 0;
  int j; for (j = 0; j < game->columns; ++j)
  {
    while(con < game->rows)
    {
      if (game->tablero[con][j] == player)
      {
        cont++;
      }
      con++;
    }
    if (cont == game->win_size)
    {
      return true;
    }
    else
    {
      cont = 0;
      con=0;
    }
  }
  cont = 0;
  con=0;

  int i; for (i = 0; i < game->rows; ++i)
  {
    while(con < game->columns)
    {
      if (game->tablero[i][con] == player)
      {
        cont++;
      }
      con++;
    }
    if (cont == game->win_size)
    {
      return true;
    }
    else
    {
      cont = 0;
      con=0;
    }
  }
  cont = 0;
  con=0;

  if (game->rows == game->win_size && game->columns == game->win_size)
  {
    int k; for (k = 0; k < game->rows; ++k)
    {
      int l; for (l = 0; l < game->columns; ++l)
      {
        if (k - l == game->win_size-1 && game->tablero[k][l] == player)
        {
          cont++;
        }
        if(l == k && game->tablero[k][l] == player)
        {
          cont++;
        }
        if(l - k == game->win_size-1 && game->tablero[k][l] == player)
        {
          cont++;
        }
      }
    }
    if (cont == game->win_size)
    {
      return true;
    }
  }

  cont=0;
  con=0;

  if (game->rows == game->win_size && game->columns == game->win_size)
  {
    int k; for (k = 0; k < game->rows; ++k)
    {
      int l; for (l = 0; l < game->columns; ++l)
      {
        if (k == l && game->tablero[k][k] == player)
        {
          cont++;
        }
      }
    }
    if (cont == game->win_size)
    {
      return true;
    }
  }

  return false;
}
