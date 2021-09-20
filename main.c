#include <stdio.h>
#include <stdlib.h>
#include "seamcarving.h"
#include "c_img.h"

int main(void){
//     struct rgb_img *img;
//     double *best;
//     struct rgb_img *cur_im;
//     read_in_img(&img, "6x5.bin");
//     int *path;
//     //printf("%d\n", get_pixel(img,0,1,0));
//     struct rgb_img *grad;
//     //for(int i = 0; i <4 ; i++){
//         calc_energy(img,  &grad);
//         print_grad(grad);
//         dynamic_seam(grad,&best);
//         recover_path(best, grad->height, grad->width, &path);
//         remove_seam(img, &cur_im, path);
//         char filename[200];
//         //sprintf(filename, "tester%d.bin",i);
//         //write_img(cur_im, filename);
//         // destroy_image(img);
//         // destroy_image(grad);
//         // free(best);
//         // free(path);
//         // img = cur_im;
//    //}
//     destroy_image(img);
//     return 0;
// }
    //print_grad(grad);
   
    struct rgb_img *im;
    struct rgb_img *cur_im;
    struct rgb_img *grad;
    double *best;
    int *path;

    read_in_img(&im, "HJoceanSmall.bin");
    
    for(int i = 0; i <150; i++){
        printf("i = %d\n", i);
        calc_energy(im,  &grad);
        dynamic_seam(grad, &best);    
        recover_path(best, grad->height, grad->width, &path);
        remove_seam(im, &cur_im, path);

        char filename[200];
        sprintf(filename, "img%d.bin", i);
        write_img(cur_im, filename);


        destroy_image(im);
        destroy_image(grad);
        free(best);
        free(path);
        im = cur_im;
    }
    destroy_image(im);
     return 0;
}

/*


24.000000       32.000000       22.000000       18.000000       19.000000
34.000000       43.000000       34.000000       28.000000       33.000000
47.000000       52.000000       45.000000       49.000000       42.000000
60.000000       58.000000       65.000000       61.000000       63.000000
75.000000       75.00000        78.000000       81.000000       80.000000



24.000000       22.000000       22.000000       19.000000       19.000000
34.000000       45.000000       34.000000       34.000000       37.000000
45.000000       47.000000       56.000000       48.000000       48.000000
58.000000       58.000000       57.000000       67.000000       69.000000
75.000000       74.00000        73.000000       77.000000       86.000000
*/