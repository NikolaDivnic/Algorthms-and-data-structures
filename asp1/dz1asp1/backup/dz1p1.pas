program dz1p1;
type pok = ^zapis;
  zapis = record
    vrednost:integer;
    kol:integer;
    vrsta:integer;
    desno:pok;
    dole:pok;
  end;
niz = array[1..20] of pok;

var a,novi,glava,tek,prethodni,pred,prvi,odgore:pok;
  kolona,vrsta,vrsta2,kolona2,kolona3,vrsta3:niz;
  broj,i,j,d,m,n,v,k,b,l,y,c,podrazumevana,podrazumevana2,brelementa:integer;
function dodajuvrstu(var novi:pok;var vrsta :niz):pok;
        var x: integer;
begin

           tek:=vrsta[novi^.vrsta]^.desno;
           prethodni:=nil;
           x := 1;
           while (x=1) do
           begin
                if (tek=nil) then x:=0
                else
                begin
                  if (tek^.kol<novi^.kol) then
                    begin
                    prethodni :=tek;
                    tek:=tek^.desno;
                  end
                  else x:=0;
                end;
           end;
           if (prethodni=nil)
           then vrsta[novi^.vrsta]^.desno:=novi
           else prethodni^.desno:= novi;
           novi^.desno:=tek;

      dodajuvrstu:=novi;
end;
function dodajukolonu(var novi:pok;var kolona:niz):pok;

var x: integer;
begin

   tek:=kolona[novi^.kol]^.dole;
   prethodni:=nil;
   x := 1;
   while (x=1) do
   begin
        if (tek=nil) then x:=0
        else
        begin
          if (tek^.vrsta<novi^.vrsta) then
            begin
            prethodni :=tek;
            tek:=tek^.dole;
          end
          else x:=0;
        end;
   end;
   if (prethodni=nil)
   then kolona[novi^.kol]^.dole:=novi
   else prethodni^.dole:= novi;
   novi^.dole:=tek;

dodajukolonu:=novi;
end;
function ispis(m:integer;n:integer;var vrsta:niz;var kolona:niz):integer;

begin
  for i :=1 to n do
      begin
           k:=1;
           tek:=vrsta[i]^.desno;
           while (k<=m) and (tek<>nil) do
           begin
                if tek^.kol>k then write(podrazumevana)
                else begin
                   write(tek^.vrednost);
                   tek:=tek^.desno;
                end;
                k:=k+1;
                write(' ')
           end;
           while k<=m do
           begin
                write(podrazumevana,' ');
                k:=k+1;
           end;
        writeln();
      end;
    ispis:=n;
end;
function kreirajmatricu(m,n:integer;var vrsta:niz;var kolona:niz):integer;
begin

     for i:=1 to m do
     begin
       new(novi);
       novi^.dole:=nil;
       novi^.desno:=nil;
       vrsta[i]:=novi;
     end;
     for i:=1 to n do
     begin
       new(novi);
       novi^.desno:=nil;
       novi^.dole:=nil;
       kolona[i]:=novi;
     end;
    kreirajmatricu:=0;
end;

function napravimatricu(m,n:integer;var vrsta:niz;var kolona:niz):integer;
begin

     kreirajmatricu(m,n,vrsta,kolona);
     writeln('Unesite elemente:vrste ,kolone,vrednost(nekorektan unos za kraj unosa)');
     readln(i,j,v);
     while ((i>0)and(j>0)and(i<=m)and(j<=n)) do
     begin
       if v<>podrazumevana then begin
       new(novi);
       novi^.vrsta:=i;
       novi^.kol:=j;
       novi^.desno:=nil;
       novi^.dole:=nil;
       novi^.vrednost:=v;
       brelementa:=brelementa+1;
       a:=dodajuvrstu(novi,vrsta);
       a:=dodajukolonu(novi,kolona);
       end;
       readln(i,j,v);


     end;
     napravimatricu:=0;
end;
function dohvati(k:integer;l:integer;var vrsta:niz;var kolona:niz):integer;
begin

   y:=1;
   if  ((k>0)and(l>0)and(k<=m)and(l<=n)) then
   begin

      tek:=vrsta[k]^.desno;
      if tek = nil then
      begin
         y:=0;
         dohvati:=podrazumevana;
      end;
      while (y = 1)  do
        begin
          if tek^.kol>l then
            begin

               y :=0;
               dohvati:=podrazumevana;
            end
          else
          begin
            if tek^.kol=l then
            begin
              y:=0;

              dohvati:=tek^.vrednost;
            end
            else tek:=tek^.desno;
            if tek= nil then
            begin


            y :=0;
            dohvati:=podrazumevana;
            end;
          end;
        end;
   end;

end;
function postavi(i,j,v:integer;var vrsta:niz;var kolona:niz):integer;

begin

   c:=dohvati(i,j,vrsta,kolona);
   if (c<>podrazumevana)and(v = podrazumevana) then
     begin

         pred:=vrsta[i];
         tek:=vrsta[i]^.desno;
         while tek^.kol<>j do
           begin
                pred:=tek;
                tek:=tek^.desno;
           end;

         pred^.desno:=tek^.desno;
         odgore:=kolona[j]^.dole;
         if kolona[j]^.dole = tek then
           begin
                kolona[j]^.dole:=tek^.dole;
                dispose(tek);

           end

           else
           begin
              while odgore^.dole<>tek do
               begin
                 odgore:=odgore^.dole;
               end;

               odgore^.dole:=tek^.dole;
               dispose(tek);
           end;

        brelementa:=brelementa-1;
     end;
   if (c<>podrazumevana) and(v<>podrazumevana) then
   begin
     tek:=vrsta[i]^.desno;
     while (tek^.kol<>j)  do
       begin
            tek:=tek^.desno;
       end;
     tek^.vrednost:=v;

   end;
   if  (c=podrazumevana) and (v<>podrazumevana) then
   begin
       new(novi);
       novi^.vrsta:=i;
       novi^.kol:=j;
       novi^.desno:=nil;
       novi^.dole:=nil;
       novi^.vrednost:=v;
       brelementa:=brelementa+1;
       a:=dodajuvrstu(novi,vrsta);
       a:=dodajukolonu(novi,kolona);
   end;
   postavi:=0;
end;
function brisanje(var vrsta:niz;var kolona:niz):integer;
begin
   for i:=1 to m do
   begin

     tek:=vrsta[i]^.desno;
     prvi:=tek;
     while tek<>nil do
       begin
         prvi:=prvi^.desno;
         dispose(tek);
         tek:=prvi;
       end;


   end;
   brisanje :=0;
end;


begin
     broj:=1;
     writeln('1. Matrica');
     writeln('2. Podrazumevani element');
     writeln('3. Element za dohvatanje');
     writeln('4. Novi element');
     writeln('5. Broj ne podrazumevanih vrednosti');
     writeln('6. Ispis matrice');
     writeln('7. Brisanje matrice');
     writeln('8. Sabiranje matrica');
     brelementa:=0;
     while broj<10 do
       begin
           writeln('Unesite broj');
           readln(broj);
           if broj = 1 then
             begin


               writeln('Unesite dimenzije matrice');
               readln(m,n);
               b:=napravimatricu(m,n,vrsta,kolona);

             end;
           if broj = 2 then
             begin
                  writeln('Unesite podrazumevanu vrednost');
                  readln(podrazumevana);
             end;
           if broj = 3 then
           begin
             writeln('Unesite element za dohvatanje');
             readln(k,l);
             b:=dohvati(k,l,vrsta,kolona);
             writeln('Zadato polje ima vrednost ',b);
           end;
           if broj = 4 then
             begin

               writeln('Unesite kordinate i vrednost za novi element');
               readln(i,j,v);
               b:=postavi(i,j,v,vrsta,kolona);
             end;

           if broj = 5 then
           begin

             writeln('Broj nepodrazumevanih vrednosti je ',brelementa);
           end;
           if broj = 6 then b:=ispis(n,m,vrsta,kolona);
           if broj = 7 then
           begin
              b:=brisanje(vrsta,kolona);
           end;
           if broj = 8 then
           begin
                writeln('Unesite drugu matricu');
               d:=napravimatricu(m,n,vrsta2,kolona2);

               d:=kreirajmatricu(m,n,vrsta3,kolona3);
               for i:=1 to n do
                   for j:=1 to m do
                   begin
                     d:=dohvati(i,j,vrsta,kolona);
                     b:=dohvati(i,j,vrsta2,kolona2);
                     if ((b+d) <> 2*podrazumevana) then
                     begin

                       b:=b+d;
                       d:=postavi(i,j,b,vrsta3,kolona3);
                     end;
                   end;
                b:=ispis(m,n,vrsta3,kolona3);
           end;
       end;
end.

