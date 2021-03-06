#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIG_ARR_LENGTH 320
extern double InputSignal_f32_1kHz_15kHz[SIG_ARR_LENGTH];

void calc_sig_dft(double *sig_src_arr, double *sig_dest_rex_arr, double *sig_dest_imx_arr, int sig_length);
void get_dft_output_mag(double * sig_dest_mag_arr);

int main()
{
  FILE *fptr, *fptr2, *fptr3, *fptr4;

  double  Output_REX[SIG_ARR_LENGTH / 2];
  double  Output_IMX[SIG_ARR_LENGTH / 2];
  double  Output_MAG[SIG_ARR_LENGTH / 2];

  calc_sig_dft(&InputSignal_f32_1kHz_15kHz[0], &Output_REX[0], &Output_IMX[0], SIG_ARR_LENGTH);
  get_dft_output_mag(&Output_MAG[0]);

  fptr  = fopen("input_signal.dat", "w");
  for(int i = 0; i < SIG_ARR_LENGTH; i++)
  {
    fprintf(fptr, "\n%f", InputSignal_f32_1kHz_15kHz[i]);
  }
  fclose(fptr);


  fptr2 = fopen("output_rex.dat", "w");
  for(int i = 0; i < SIG_ARR_LENGTH / 2; i++)
  {
    fprintf(fptr2, "\n%f", Output_REX[i]);
  }
  fclose(fptr2);

  fptr3 = fopen("output_imx.dat", "w");
  for(int i = 0; i < SIG_ARR_LENGTH / 2; i++)
  {
    fprintf(fptr3, "\n%f", Output_IMX[i]);
  }
  fclose(fptr3);

  fptr4 = fopen("output_mag.dat", "w");
  for(int i = 0; i < SIG_ARR_LENGTH / 2; i++)
  {
    fprintf(fptr4, "\n%f", Output_MAG[i]);
  }
  fclose(fptr4);

  return 0;
}

void calc_sig_dft(double *sig_src_arr, double *sig_dest_rex_arr, double *sig_dest_imx_arr, int sig_length)
{
  int i = 0;
  int j = 0;
  int k = 0;

  double PI = 3.14159265359;
  
  /// WHY / 2
  for(j = 0; j < sig_length / 2; j++)
  {
    sig_dest_rex_arr[j] = 0;
    sig_dest_imx_arr[j] = 0;
  }

  for(k = 0; k < sig_length / 2; k++)
  {
    for(i = 0; i < sig_length; i++)
    {
      /// WHT this formula
      sig_dest_rex_arr[k] = sig_dest_rex_arr[k] + sig_src_arr[i] * cos(2 * PI * k * i / sig_length);
      sig_dest_imx_arr[k] = sig_dest_imx_arr[k] - sig_src_arr[i] * sin(2 * PI * k * i / sig_length);
    }
  }
}

void get_dft_output_mag(double * sig_dest_mag_arr)
{
  int k = 0;

  double  Output_REX[SIG_ARR_LENGTH / 2];
  double  Output_IMX[SIG_ARR_LENGTH / 2];

  for(k = 0; k < SIG_ARR_LENGTH / 2; k++)
  {
    sig_dest_mag_arr[k] = sqrt(pow(Output_REX[k], 2) * pow(Output_IMX[k], 2));
  }
}
