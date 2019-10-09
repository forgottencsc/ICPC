
### Burnside引理/Polya定理

给定作用于有限集$X$上的有限群$G$，这里我们直接考虑$G$的置换表示。

定义：

$T(x)=\{y \in X | \exist g \in G,y = gx\}$为$x$的$G$-轨道。

$x$的稳定化子$G_x=\{g|gx=x\}$

置换特征标$\chi(g)=\{x|gx=x\}$，即在$g$的作用下不变的$x$。

可以证明所有轨道构成了$X$的一个划分，即轨道两两不相交。

定理(轨道-稳定化子)：

$|T(x)||G_x|=|G|$

证明：

令$G$作用于$T(x)$上可得到一个自然的群同态$\varphi:G\rightarrow S(T(x))$

这个同态的

定理(Burnside)：

$X$在$G$作用下的轨道数为

$$
\frac{1}{|G|}\sum_{g \in G}|\chi(g)|
$$

证明：

$$
轨道数=\sum_{x \in X}\frac 1 {|T(x)|}=\sum_{x \in X} \frac{|G_x|}{|G|}=\frac{1}{|G|}\sum_{x \in X}|G_x|
$$

$$
=\frac 1 {|G|} |\{(g,x)|gx=x\}|
=\frac 1 {|G|}\sum_{g \in G}|\chi(g)|
$$
