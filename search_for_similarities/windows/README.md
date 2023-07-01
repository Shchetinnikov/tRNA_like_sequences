#  Multiple alignment for finding exon-intron and intron-exon boundaries | Graduate work
<p>Software is proposed that allows to find the boundaries of exon-intron and intron-exon in a given sequence according to the original multiple alignment.</p>
<p>The approach is based on the sliding window method with sequential application of dynamic programming taking into account the correlation of neighboring base pairs.</p>
National Research Nuclear University MEPhI (Moscow Engineering Physics Institute).

## Project structure
The program consists of several entities:
<ul>
  <li>Alignment:
    <p>the class of the original multiple alignment for this type of border;</p></li>
  <li>NeedlemanWunsch:
    <p>a dynamic programming class taking into account the correlation of neighboring bases;</p></li>
  <li>SlidingWindow:
    <p>the class of a window sliding along the sequence under study with a step of 10 bases.</p></li>
</ul>