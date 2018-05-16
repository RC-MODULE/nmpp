
void InitTimer()
{
    asm volatile(     "push ar7, gr7;            \n\t"
                    "with gr7 = false;     		\n\t"    //    timer setup 1
                    "[40000804h] = gr7;        \n\t"     //    timer setup 2
                    "gr7 = 0fh;                \n\t"     //    timer setup 3
                    "[40000806h] = gr7;        \n\t"     //    timer setup 4
                    "pop ar7, gr7;");
}