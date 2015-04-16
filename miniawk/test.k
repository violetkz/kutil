case1: 
------
        {pfunc ($1 $2);}
case2: 
------
        /virtio/ {
                
                dependlist =  split($4, ','); 
               
                if (str ~ /[0-9]+/) {
                   id = str; 
                }
                
                if (str ~ /(\d+):(\d+):/) {
                    year = $g1;
                    month = $g2;
                }

                pfunc($m, year, month, depenlist);
                
                }

1.   token:  if else for 
     operator: ==  =  + - ~ /
     builtin func: split substr len print
