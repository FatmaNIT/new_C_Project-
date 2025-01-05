#include <stdio.h>
#include <SDL.h>


void linear_regression(double x[], double y[], int n, double *m, double *c) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    *m = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    *c = (sum_y - (*m) * sum_x) / n;
}

void print_table(double x[], double y[], int n) {
    printf("\n+-----------+-----------+\n");
    printf("|    x      |    y      |\n");
    printf("+-----------+-----------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %9.2lf | %9.2lf |\n", x[i], y[i]);
    }
    printf("+-----------+-----------+\n");
}

void visualize(double x[], double y[], int n, double m, double c) {
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Window *window = SDL_CreateWindow("Linear Regression Visualization",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);

    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window , -1, SDL_RENDERER_ACCELERATED); 
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderDrawLine(renderer, 50, 550, 750, 550);     
    SDL_RenderDrawLine(renderer, 50, 50, 50, 550);        

    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); 
    for (int i = 0; i < n; i++) {
        int px = 50 + (int)(x[i] * 50);  
        int py = 550 - (int)(y[i] * 50);
        SDL_RenderDrawPoint(renderer, px, py);
    }

    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    int x1 = 0, y1 = (int)(m * 0 + c); 
    int x2 = 14, y2 = (int)(m * 14 + c); 
    SDL_RenderDrawLine(renderer,
                       50 + x1 * 50, 550 - y1 * 50,
                       50 + x2 * 50, 550 - y2 * 50);

    SDL_RenderPresent(renderer);
    SDL_Delay(5000); 

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main (int argc, char *argv[]){
    int n;
    printf("Enter the number of data points: ");
    scanf("%d", &n);

    double x[n], y[n];
    printf("Enter the x and y values:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d]: ", i + 1);
        scanf("%lf", &x[i]);
        printf("y[%d]: ", i + 1);
        scanf("%lf", &y[i]);
    }

    double m, c;
    linear_regression(x, y, n, &m, &c);

    printf("\nThe linear regression line is: y = %.2lfx + %.2lf\n", m, c);

    
    print_table(x, y, n);

    
    visualize(x, y, n, m, c);
//naoufel 
    return 0;
}
