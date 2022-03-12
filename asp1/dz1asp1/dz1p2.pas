program dz1p2;
const maxduz = 100;
type  niz = array[1..maxduz] of integer;
  zapis = record
     redp:niz;
     rear:integer;
     mark:array [1..maxduz] of boolean;
     brelementa:integer;
     brojmark:integer;
     maxelem:integer;
     front:integer;
     end;
var red:zapis;
  broj,x,maxbrelem,element:integer;
function napravired(maxbrelem:integer):integer;
var i:integer;
begin
  red.brelementa:=0;
  red.brojmark:=0;
  red.maxelem:=maxbrelem;
  for i:=1 to red.maxelem do
  begin
    red.mark[i]:=false;
    red.redp[i]:=0;
  end;
  red.front:=1;
  red.rear:=1;

  napravired:=0;
end;
function unesielement(element:integer;var red:zapis):integer;
var i:integer;
begin
   red.brelementa:=red.brelementa + 1;
   if red.brojmark>0 then
   begin
     i:=red.rear-1;
      while red.mark[i] = false do
            begin
              i:=i-1;
              if i = 0 then i:=red.maxelem;
            end;
      red.redp[i]:=element;
      red.brojmark:=red.brojmark - 1;
      red.mark[i]:=false;
   end
   else
   begin
      red.redp[red.rear]:=element;
      red.rear:=red.rear mod red.maxelem +1;

   end;
   unesielement:=0;
end;
function izbacielement(var red:zapis):integer;
var najmanji,index,i:integer;
begin
  i:=red.front;
  najmanji:=red.redp[i];
  index:=i;
  while i<>red.rear do
        begin
           if ((red.redp[i]<najmanji) and (red.mark[i] =false)) then
           begin
                index:=i;
                najmanji:=red.redp[i];
           end;
           i:=i mod red.maxelem + 1;
        end;

  red.brojmark:=red.brojmark + 1;
  red.brelementa:=red.brelementa - 1;
  izbacielement:=najmanji;
  red.mark[index]:=true;

  while red.mark[red.front]=true do
        begin
         red.brojmark:=red.brojmark - 1;
          red.mark[index]:=false;
          red.front:=red.front mod red.maxelem +1;
        end;


  if red.brelementa = 0 then
  begin
     red.rear:=1;
     red.front:=1;
     for i:=1 to red.maxelem do
      begin
    red.mark[i]:=false;
    red.redp[i]:=0;
    end;
  end;
end;
function ispis(var red:zapis):integer;
var i:integer;
begin
  i:=red.front;
  while i<>red.rear do
        begin
           write('red[',i,'] = ');
           if red.mark[i]= true then writeln('*' )
           else writeln(red.redp[i]);
           i:=i mod red.maxelem + 1
        end;
  ispis:=0;
end;
begin
  broj:=1;
  writeln('Unesite broj ');
  writeln('1. Napravi red');
  writeln('2. Unesi element');
  writeln('3. Izbaci element');
  writeln('4. Ispisi');
  writeln('5. Prvi bez brisanja');
  writeln('6. Maksimalni broj elementa');
  writeln('7. Broj elementa reda');
  while broj<10 do
        begin
  writeln('Unesite broj ');
  readln(broj);

  case broj of
  1 : begin  Writeln('Unesite max broj elementa reda');
        readln(maxbrelem);
        napravired(maxbrelem);
      end;
  2:begin
        if red.brelementa<red.maxelem then
        begin
          writeln('Unesite element');
          readln(element);
          unesielement(element,red)
        end
        else writeln('Red je pun');
    end;
   3:begin
    if red.brelementa  = 0 then writeln('Red je prazan')
    else
    begin
        x:=izbacielement(red);
        writeln('Izbaceni element je ',x);

    end;

    end;
    4:begin
           ispis(red);
      end;

    5:writeln(red.front);
    6:writeln(red.maxelem);
    7:writeln(red.brelementa);
  end;



        end;
  readln(broj);


end.

