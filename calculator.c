/*
 * Calculator.c
 * Run with gcc calculator.c `pkg-config gtk+-2.0 --cflags pkg-config gtk+-2.0 --libs` ; ./a.out
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "integral.h"
#include <gtk/gtk.h>

/**
 * Custom Double to ASCII converter
 */
char * dtoa(char *s, double n) {
    static double PRECISION = 0.00000000000001;
    static int MAX_NUMBER_STRING_SIZE = 32;
    // handle special cases
    if (isnan(n)) {
        strcpy(s, "nan");
    } else if (isinf(n)) {
        strcpy(s, "inf");
    } else if (n == 0.0) {
        strcpy(s, "0");
    } else {
        int digit, m, m1;
        char *c = s;
        int neg = (n < 0);
        if (neg)
            n = -n;
        // calculate magnitude
        m = log10(n);
        int useExp = (m >= 14 || (neg && m >= 9) || m <= -9);
        if (neg)
            *(c++) = '-';
        // set up for scientific notation
        if (useExp) {
            if (m < 0)
               m -= 1.0;
            n = n / pow(10.0, m);
            m1 = m;
            m = 0;
        }
        if (m < 1.0) {
            m = 0;
        }
        // convert the number
        while (n > PRECISION || m >= 0) {
            double weight = pow(10.0, m);
            if (weight > 0 && !isinf(weight)) {
                digit = floor(n / weight);
                n -= (digit * weight);
                *(c++) = '0' + digit;
            }
            if (m == 0 && n > 0)
                *(c++) = '.';
            m--;
        }
        if (useExp) {
            // convert the exponent
            int i, j;
            *(c++) = 'e';
            if (m1 > 0) {
                *(c++) = '+';
            } else {
                *(c++) = '-';
                m1 = -m1;
            }
            m = 0;
            while (m1 > 0) {
                *(c++) = '0' + m1 % 10;
                m1 /= 10;
                m++;
            }
            c -= m;
            for (i = 0, j = m-1; i<j; i++, j--) {
                // swap without temporary
                c[i] ^= c[j];
                c[j] ^= c[i];
                c[i] ^= c[j];
            }
            c += m;
        }
        *(c) = '\0';
    }
    return s;
}

/*
 * UI elements delcaration  
*/
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *integral_w_l;
    GtkWidget *running_from_l;
    GtkWidget *a_l;
    GtkWidget *b_l;
    GtkWidget *result_l;

    GtkWidget *integral_w;
    GtkWidget *a;
    GtkWidget *b;
    GtkWidget *result_w;

    GtkWidget *box1;
    GtkWidget *table;

    GtkWidget *image;
 
/**
 * Genrates graph by passing params to plotter.py
 */
void generate_graph(float a, float b, char* e) {
    
    FILE * fptr = fopen ("cache/points.txt","w"); 

    float N = 100;
    for (int i=0; i<N; i++) {
        float x = (b-a)*i/N + a;
        float y = parseAt(e, x);
        
        fprintf(fptr, "%f %f\n", x, y);
        //fputs(line, fptr);
    }

    fclose (fptr);
    system("python3 plotter.py");

}
void generate_graph_c(char* a, char* b, char* e) {
    generate_graph(atof(a), atof(b), e);
}

/* Button press callback function.
 * Starts the integrator (A blocking Function)
*/
static void run_integrator( GtkWidget *widget, gpointer   data ) {
    gtk_label_set_text(result_w, "Loading");
    
    char *exp = gtk_entry_get_text (integral_w);

    char *a1 = gtk_entry_get_text (a);
    char *b1 = gtk_entry_get_text (b);

    generate_graph_c(a1, b1, exp);

    float res = integral_c(a1, b1, exp);

    printf("integral of %s = %f\n", exp, res);

    char res1[50];
    dtoa(res1, res);

    gtk_label_set_text(result_w, res1);
    gtk_image_set_from_pixbuf(image, gdk_pixbuf_new_from_file("cache/output.png", NULL));
}

/* Callback to Kill the program*/
static void destroy( GtkWidget *widget, gpointer   data ) {
    gtk_main_quit ();
}

/**
 * Kills the program (Runs on Close Button press)
 */
static gboolean delete_event( GtkWidget *widget, GdkEvent  *event, gpointer   data ) {
    /* If you return FALSE in the "delete-event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

    g_print ("delete event occurred\n");

    destroy(widget, data);
    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete-event". */

    return TRUE;
}


/**
 * Defines the UI elements and starts the GUI main loop gtk_main ();
 */
int main( int   argc,char *argv[] ) {
    /* GtkWidget is the storage type for widgets */

    
    /* This is called in all GTK applications. Arguments are parsed
     * from the command line and are returned to the application. */
    gtk_init (&argc, &argv);
    
    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    /* When the window is given the "delete-event" signal (this is given
     * by the window manager, usually by the "close" option, or on the
     * titlebar), we ask it to call the delete_event () function
     * as defined above. The data passed to the callback
     * function is NULL and is ignored in the callback function. */
    g_signal_connect (window, "delete-event",
		      G_CALLBACK (delete_event), NULL);
    
    /* Here we connect the "destroy" event to a signal handler.  
     * This event occurs when we call gtk_widget_destroy() on the window,
     * or if we return FALSE in the "delete-event" callback. */
    g_signal_connect (window, "destroy",
		      G_CALLBACK (destroy), NULL);
    
    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /* We create a box to pack widgets into.  This is described in detail
     * in the "packing" section. The box is not really visible, it
     * is just used as a tool to arrange widgets. */
    box1 = gtk_hbox_new (FALSE, 0);
    table = gtk_table_new(5, 3, FALSE);
    image = gtk_image_new_from_file ("cache/blank.png");

    /* Put the box into the main window. */
    gtk_container_add (GTK_CONTAINER (window), box1);

    integral_w_l = gtk_label_new("Integral of ");
    integral_w = gtk_entry_new();
    a = gtk_entry_new();
    b = gtk_entry_new();
    running_from_l = gtk_label_new("Running from ");
    a_l = gtk_label_new("a = ");
    b_l = gtk_label_new("b = ");
    result_l = gtk_label_new("Result = ");
    result_w = gtk_label_new("0.0");

    /* Creates a new button with the label "Hello World". */
    button = gtk_button_new_with_label ("Integrate");
    
    /* When the button receives the "clicked" signal, it will call the
     * function hello() passing it NULL as its argument.  The hello()
     * function is defined above. */
    g_signal_connect (button, "clicked",
		      G_CALLBACK (run_integrator), NULL); 
    

    /* This packs the button into the window (a gtk container). */
    gtk_table_attach_defaults(GTK_TABLE(table), integral_w_l, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), integral_w, 1, 2, 0, 1);

    gtk_table_attach_defaults(GTK_TABLE(table), image, 0, 2, 1, 2);

    gtk_table_attach_defaults(GTK_TABLE(table), running_from_l, 0, 2, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), a_l, 0, 1, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(table), a, 1, 2, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(table), b_l, 0, 1, 4, 5);
    gtk_table_attach_defaults(GTK_TABLE(table), b, 1, 2, 4, 5);

    gtk_table_attach_defaults(GTK_TABLE(table), result_l, 0, 1, 5, 6);
    gtk_table_attach_defaults(GTK_TABLE(table), result_w, 1, 2, 5, 6);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 0, 1, 6, 7);

    gtk_box_pack_start (GTK_BOX(box1), table, TRUE, TRUE, 0);

    /*gtk_box_pack_start (GTK_BOX(box1), integral_w_l, FALSE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(box1), integral_w, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(box1), running_from_l, FALSE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(box1), a_l, FALSE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(box1), a, FALSE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(box1), b_l, FALSE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(box1), b, FALSE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(box1), result_l, FALSE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(box1), result, FALSE, TRUE, 0);

    gtk_box_pack_start (GTK_BOX(box1), button, FALSE, TRUE, 0);*/
    
    /* The final step is to display this newly created widget. */
    gtk_widget_show (button);
    gtk_widget_show (image);
    gtk_widget_show (integral_w_l);
    gtk_widget_show (integral_w);
    gtk_widget_show (running_from_l);
    gtk_widget_show (a_l);
    gtk_widget_show (a);
    gtk_widget_show (b_l);
    gtk_widget_show (b);
    gtk_widget_show (result_l);
    gtk_widget_show (result_w);
    
    gtk_widget_show (table);

    gtk_widget_show (box1);
    
    /* and the window */
    gtk_widget_show (window);
    
    /* All GTK applications must have a gtk_main(). Control ends here
     * and waits for an event to occur (like a key press or
     * mouse event). */
    gtk_main ();
    
    return 0;
}
 