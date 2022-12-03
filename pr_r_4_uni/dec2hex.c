/*
Напишите программу dec2hex, имеющую один аргумент – десятичное натуральное число и выводящее
соответствующее 16-ое число. Пример вызова: ./dec2hex 125
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>

void
dec_to_hex (int input)
{
  int ost = 0;
  char hex[256] = { 0 };
  char correct_hex[256] = { 0 };
  int i = 0;
  while (input != 0)
    {
      ost = input % 16;
      switch (ost)
	{
	case 0:
	  {
	    hex[i] = '0';
	    break;
	  };
	case 1:
	  {
	    hex[i] = '1';
	    break;
	  };
	case 2:
	  {
	    hex[i] = '2';
	    break;
	  };
	case 3:
	  {
	    hex[i] = '3';
	    break;
	  };
	case 4:
	  {
	    hex[i] = '4';
	    break;
	  };
	case 5:
	  {
	    hex[i] = '5';
	    break;
	  };
	case 6:
	  {
	    hex[i] = '6';
	    break;
	  };
	case 7:
	  {
	    hex[i] = '7';
	    break;
	  };
	case 8:
	  {
	    hex[i] = '8';
	    break;
	  };
	case 9:
	  {
	    hex[i] = '9';
	    break;
	  };
	case 10:
	  {
	    hex[i] = 'A';
	    break;
	  };
	case 11:
	  {
	    hex[i] = 'B';
	    break;
	  };
	case 12:
	  {
	    hex[i] = 'C';
	    break;
	  };
	case 13:
	  {
	    hex[i] = 'D';
	    break;
	  };
	case 14:
	  {
	    hex[i] = 'E';
	    break;
	  };
	case 15:
	  {
	    hex[i] = 'F';
	    break;
	  };
	default:
	  printf ("ERROR: can't translate\n");
	}
      input /= 16;
      ++i;
    };
  int j = strlen (hex);
  for (int i = 0; i < strlen (hex); i++)
    {
      correct_hex[i] = hex[j - 1];
      j--;
    }
  printf ("Your number in hex: %s\n", correct_hex);

}

int
main (int argc, char *argv[])
{
  printf ("Your string: %s\n", argv[1]);
  char *input_hex[256];
  int input = 0;
  if (argc > 2)
    {
      puts ("ERROR: Too many arguments");
      return 1;
    }
  if (atoi (argv[1]) != 0)
    {
      input = atoi (argv[1]);
      printf ("Your number in dec: %d\n", input);
      dec_to_hex (input);

    }
  else
    {
      puts ("ERROR: Not a number");
      return 1;
    }
  return 0;
}
