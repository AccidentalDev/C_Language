void generaDatos(int arr[],int n){
   int i,rand,temp;
   for(i=0;i<n;++i)
      arr[i]=i+1;
   randomize();
   for(i=0;i<n;++i)
      rand=random(n);
      temp=arr[rand];
      arr[rand]=arr[i];
      arr[i]=temp;
}