program
begin

    void printGuiones( ) extern;
    void print(integer n) extern;

    // retorna el n esimo primo
    integer nthprime (integer n) 
      begin
        integer i, divs;
        bool divides;
        i = 0;
        divs = 2;
        n = n+1;
        while ( n > 0) 
          begin
            divides = false; 
            i = i + 1;
            while ( (! divides) && (divs < i))
              begin
                if ((i%divs) == 0) then
                  begin
                    divides = true;
                  end
                else
                  begin
                    divs = divs+1;
                  end
              end
            divs = 2;
            if (!divides) then
              begin
                n = n-1;
              end
          end
        return i;
    end

    void main()
      begin
        integer x, i, aux, res;
        // test nthprime entero
        printGuiones(); // printf("-----------")
        x=10; // cantidad de veces que ejecutara la funcion
        i = 0;
        aux = 4;
        while (i<x)
          begin
            res = nthprime(aux);
            aux = aux + 1;
            print( res);
            i=i+1;
          end
      end
end