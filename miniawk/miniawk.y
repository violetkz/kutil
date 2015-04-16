%{

%}

%%
start : empty pattern_action_list;

empty: 
     { /* do nothing */; }
     ;

pattern_action_list:
   pattern_action             { $$ = node($1, node_rule_list, NULL); }
   | pattern_action_list rule { $$ = append_right($1, node($2, node_rule_list, NULL));}
   ;

rule : pattern action         { $$ = node($1, node_rule, $2); }
     ;

pattern: /* empty */          {$$ = NULL;}
       | conditional          { $$ = $1; }
     

%%
                   
