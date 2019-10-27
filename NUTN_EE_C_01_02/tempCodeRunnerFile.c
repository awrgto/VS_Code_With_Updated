dvsPeek(&c_last, &f_last, Stack);
                    if(oprPriority(c_last) < oprPriority(c_infix)) break;
                    puts("prepop");
                    dvsPop(&c_pop, &i_pop, Stack);
                    dvsPush(