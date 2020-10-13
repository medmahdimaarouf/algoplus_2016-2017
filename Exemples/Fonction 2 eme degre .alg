<Algo desc="Resolution de fonction de 2 eme degre &#xa;" name="Sans titre">
<variables>
<var type="entier" name="a"/>
<var type="entier" name="b"/>
<var type="entier" name="c"/>
<var type="reel" name="x"/>
<var type="reel" name="d"/>
</variables>
<Debut>
<item var="a" msg="&quot;Donner A  : &quot;" index="2"/>
<item var="b" msg="&quot;Donner B  : &quot;" index="2"/>
<item var="c" msg="&quot;Donner C  : &quot;" index="2"/>
<item exp="Carre(b) - 4 * a * c" var="d" index="1"/>
<item condition="d &lt; 0" index="5">
<item msg="&quot;EQ N ADMET PAS DE SOLUOTION &quot;" index="3"/>
<item index="6">
<item condition="d == 0" index="5">
<item msg="&quot; X  =  &quot; + (- b / 2 * a)" index="3"/>
<item index="6">
<item msg="&quot;X1 = &quot; + (-b - Racine(d)) / 2  * a" index="3"/>
<item msg="&quot;X2 = &quot; + (-b + Racine(d)) / 2  * a" index="3"/>
</item>
<item app="FIN SI" index="0"/>
</item>
</item>
<item app="FIN SI" index="0"/>
</item>
</Debut>
</Algo>
