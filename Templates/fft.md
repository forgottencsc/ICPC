$$f(x,y)=\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}a_{ij}x^iy^j$$

$$f(x,y)g(x,y)=\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}\left(\sum_{k=0}^{i}\sum_{l=0}^{j}a_{kl}b_{i-k,j-l}\right)x^iy^j$$

$$f(\omega^u,\omega^v)=\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}a_{ij}\omega^{ui+vj}$$

定义：

$$f_{00}(x,y)=\sum_{i=0}^{\frac n2-1}\sum_{j=0}^{\frac n2-1}a_{2i,2j}x^{i}y^{j}$$

$$f_{01}(x,y)=\sum_{i=0}^{\frac n2-1}\sum_{j=0}^{\frac n2-1}a_{2i,2j+1}x^{i}y^{j}$$

$$f_{10}(x,y)=\sum_{i=0}^{\frac n2-1}\sum_{j=0}^{\frac n2-1}a_{2i+1,2j}x^{i}y^{j}$$

$$f_{11}(x,y)=\sum_{i=0}^{\frac n2-1}\sum_{j=0}^{\frac n2-1}a_{2i+1,2j+1}x^{i}y^{j}$$

接下来考虑

$$f(\omega^u_n,\omega^v_n)=\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}a_{ij}\omega^{ui+vj}_n$$

$$=\sum_{i=0}^{\frac n2-1}\sum_{j=0}^{\frac n2-1}a_{2i,2j}\omega^{2ui+2vj}_n+\sum_{i=0}^{\frac n2-1}\sum_{j=0}^{\frac n2-1}a_{2i,2j+1}\omega^{2ui+2vj+v}_n$$

$$=\sum_{i=0}^{\frac n2-1}\sum_{j=0}^{\frac n2-1}a_{2i+1,2j}\omega^{2ui+2vj+u}_n+\sum_{i=0}^{\frac n2-1}\sum_{j=0}^{\frac n2-1}a_{2i+1,2j+1}\omega^{2ui+2vj+u+v}_n$$

$$=f_{00}(\omega^u_\frac n2,\omega^v_\frac n2)+\omega^vf_{01}(\omega^u_\frac n2,\omega^v_\frac n2)+\omega^uf_{10}(\omega^u_\frac n2,\omega^v_\frac n2)+\omega^{u+v}f_{11}(\omega^u_\frac n2,\omega^v_\frac n2)$$

略去过程，可得

$$f(\omega^u_n,\omega^v_n)=f_{00}(\omega^u_\frac n2,\omega^v_\frac n2)+\omega^vf_{01}(\omega^u_\frac n2,\omega^v_\frac n2)+\omega^uf_{10}(\omega^u_\frac n2,\omega^v_\frac n2)+\omega^{u+v}f_{11}(\omega^u_\frac n2,\omega^v_\frac n2)$$

$$f(\omega^u_n,\omega^{v+\frac n2}_n)=f_{00}(\omega^u_\frac n2,\omega^v_\frac n2)-\omega^vf_{01}(\omega^u_\frac n2,\omega^v_\frac n2)+\omega^uf_{10}(\omega^u_\frac n2,\omega^v_\frac n2)-\omega^{u+v}f_{11}(\omega^u_\frac n2,\omega^v_\frac n2)$$

$$f(\omega^{u+\frac n2}_n,\omega^v_n)=f_{00}(\omega^u_\frac n2,\omega^v_\frac n2)+\omega^vf_{01}(\omega^u_\frac n2,\omega^v_\frac n2)-\omega^uf_{10}(\omega^u_\frac n2,\omega^v_\frac n2)-\omega^{u+v}f_{11}(\omega^u_\frac n2,\omega^v_\frac n2)$$

$$f(\omega^{u+\frac n2}_n,\omega^{v+\frac n2}_n)=f_{00}(\omega^u_\frac n2,\omega^v_\frac n2)-\omega^vf_{01}(\omega^u_\frac n2,\omega^v_\frac n2)-\omega^uf_{10}(\omega^u_\frac n2,\omega^v_\frac n2)+\omega^{u+v}f_{11}(\omega^u_\frac n2,\omega^v_\frac n2)$$

NTT一遍正一遍负可得

$$
c_{xy}=\sum_{u=0}^{n-1}\sum_{v=0}^{n-1}b_{uv}\omega^{-ux-vy}_{n}=\sum_{u=0}^{n-1}\sum_{v=0}^{n-1}\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}a_{ij}\omega^{u(i-x)+v(j-y)}_{n}
$$

$$
=\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}a_{ij}\sum_{u=0}^{n-1}\sum_{v=0}^{n-1}\omega^{u(i-x)+v(j-y)}_{n}
$$

$$
\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}a_{ij}\sum_{u=0}^{n-1}\sum_{v=0}^{n-1}\omega^{u(i-x)+v(j-y)}_{n}=\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}a_{ij}\sum_{u=0}^{n-1}\omega_{n}^{(i-x)u}\sum_{v=0}^{n-1}\omega_{n}^{(j-y)v}
$$

$$
=n^2\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}a_{ij}[i==x\wedge j==y]=n^2a_{xy}
$$
