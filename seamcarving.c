#include <stdio.h>
#include <stdlib.h>
#include "seamcarving.h"
#include "c_img.h"
#include <math.h>
#define MIN(x,y) ((x)<(y)? (x):(y))


void calc_energy(struct rgb_img *im, struct rgb_img **grad){
     int w = im->width;
     int h = im->height; 
     create_img(grad,h,w);
    for(int y = 0;y < h; y++){
        for(int x = 0;x < w; x++){
            int rx =300,ry =300,bx = 300,by = 300,gx =300,gy = 300;
            int energy;
            int deltax =0;
            int deltay=0;

            
           if(x+1 >= w){
                rx = (get_pixel(im,y,0,0)) - (get_pixel(im,y,x-1,0));            
                gx = (get_pixel(im,y,0,1)) - (get_pixel(im,y,x-1,1));           
                bx = (get_pixel(im,y,0,2)) - (get_pixel(im,y,x-1,2));
            
           }if(x-1 <0){
                rx = (get_pixel(im,y,x+1,0)) - (get_pixel(im,y,w-1,0)); //w-1? or w?
                gx = (get_pixel(im,y,x+1,1)) - (get_pixel(im,y,w-1,1));
                bx = (get_pixel(im,y,x+1,2)) - (get_pixel(im,y,w-1,2));
           }if(y-1<0){
                
                ry = (get_pixel(im,y+1,x,0)) - (get_pixel(im,h-1,x,0));            
                gy = (get_pixel(im,y+1,x,1)) - (get_pixel(im,h-1,x,1));            
                by = (get_pixel(im,y+1,x,2)) - (get_pixel(im,h-1,x,2));
           }if(y+1>=h){
                ry = (get_pixel(im,0,x,0)) - (get_pixel(im,y-1,x,0));            
                gy = (get_pixel(im,0,x,1)) - (get_pixel(im,y-1,x,1));            
                by = (get_pixel(im,0,x,2)) - (get_pixel(im,y-1,x,2)); 
           }if(rx==300){
               
               rx = (get_pixel(im,y,x+1,0)) - (get_pixel(im,y,x-1,0));
               gx = (get_pixel(im,y,x+1,1)) - (get_pixel(im,y,x-1,1));
               bx = (get_pixel(im,y,x+1,2)) - (get_pixel(im,y,x-1,2));
               
          }if(ry == 300){
                
               ry = (get_pixel(im,y+1,x,0)) - (get_pixel(im,y-1,x,0));
               gy = (get_pixel(im,y+1,x,1)) - (get_pixel(im,y-1,x,1));
               by = (get_pixel(im,y+1,x,2)) - (get_pixel(im,y-1,x,2));
           }
               
            deltax = pow(rx,2) + pow(gx,2) + pow(bx,2);
            deltay = pow(ry,2) + pow(gy,2) + pow(by,2);
            energy = sqrt((double)(deltax + deltay));
            uint8_t eng = (uint8_t)(energy/10);
            set_pixel(*grad, y,x,eng,eng,eng);// we set it im which is then overriding it

            
        }
        }
        

}
double get_min(double a, double b){
     if(a<b){
          return a;
     }else{
          return b;
     }
}

void dynamic_seam(struct rgb_img *grad, double **best_arr){  
     //Ask about printing array
     int w = grad->width;
     int h = grad->height;
     *best_arr= (double *)malloc(sizeof(double)*w*h);
     int left;
     int right;
     int top;
     double min;

     for(int j = 0; j<w;j++){
          (*best_arr)[j] = (double)(get_pixel(grad,0,j,0));
          //printf("%lf\n", (*best_arr)[j]);
     }
     
     for(int j = 1; j<h;j++){
          for(int i = 0; i<w;i++){
               top = i;
               if(i>0){
                    left = i-1;
               }
              else{
                   left = 0;
              }
              if(i<w-1){
                   right = i+1;
              }
              else{
                   right = w-1;
              }
              min = get_min((*best_arr)[(j-1)*w+left],(*best_arr)[(j-1)*w+right]);
              min = get_min(min, (*best_arr)[(j-1)*w+top]);
              (*best_arr)[j*w+i] =(double) get_pixel(grad,j,i,0) + min;
              
          } 
             
     }
//      for(int y = 0;y < h; y++){

//           for(int x = 0;x < w; x++){
//                printf("%lf\n",(*best_arr)[y*w+x]);
     
// }
//       }
}
int get_ind(double *temp_arr, int ind){
     
     //int i = 0;
     int counter = 0;
     for(int i = 1; i<3; i++){
          if((temp_arr[i])<(temp_arr[counter])){
               counter = i;
               }          
          }
          return ind - counter;
     }
int get_bott_ind(double *best, int value, int h, int w){
     int j = h-1;
     //int i = 0;
     
     for(int i = 0; i<w; i++){
          if((best)[(h-1)*w+i] == value){
               return i;
          }          
          }
     }
int get_min2(int a, int b, int c){
     if(a<b && a<c){
         return a; 
     }else if(b<a && b<c){
          return b;
     }else{
          return c;
     }
     
}

void recover_path(double *best, int height, int width, int **path){
     
   //print_path(*path, 5);

     int left;
     int right;
     int right_ind;
     int left_ind;
     int top;
     int min=10000; //ask about this
     int ind;
     int cur;
     double *temp_arr = (double *)malloc(sizeof(double)*3);
     *path = (int *)malloc(sizeof(int)*height);

     for(int j = 0; j<width;j++){
          cur = (best)[(height-1)*width+j];
          min = get_min((best)[(height-1)*width+j],min);
     }
     ind = get_bott_ind(best,min,height, width);
     (*path)[height-1] = ind;

     
              

     for(int j = height-2; j>=0;j--){
          int beg = (*path)[j+1] + 1;
         //int beg = 6;
          
          for(int i = 0; i<3;i++){    
               if(beg - i < 0){
                   temp_arr[2] = best[j*width]; 
               }else if (beg - i >width -1){
                    temp_arr[0] = best[j*width+beg+i-1];
                }
               else{
                    temp_arr[i] = best[j*width+beg-i];
               }
        
        
    }  
          if(beg > width-1){
               //min = get_min2((best)[(j-1)*width+left],(best)[(j-1)*width+right],(best)[(j-1)*width+top]);
               (*path)[j] = get_ind(temp_arr,width);
          }else if(beg <= 1){
               (*path)[j] = get_ind(temp_arr,1);
          }else{
               (*path)[j] = get_ind(temp_arr,beg);
          }
//           ind = get_ind(best,min,j,width);  
//           (*path)[j-1] = ind;
// }
     // for(int i = 0; i<height; i++){
     //      printf("%d\n", (*path)[i]);
     // }
     
}
}
void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path){
     int h = src->height;
     int w = src->width;
     uint8_t red,blue,green;
     create_img(dest,h,w-1);

     for(int i = 0; i<h;i++){
          for(int j = 0; j<w;j++){
               if(j < path[i]){
                    red = get_pixel(src, i,j,0);
                    green =  get_pixel(src, i,j,1);
                    blue =  get_pixel(src, i,j,2);
                    set_pixel(*dest,i,j,red,green,blue);
               }else if(j>path[i]){
                    red = get_pixel(src, i,j,0);
                    green =  get_pixel(src, i,j,1);
                    blue =  get_pixel(src, i,j,2);
                    set_pixel(*dest,i,j-1,red,green,blue);
               }

               }
          }
     }

     


