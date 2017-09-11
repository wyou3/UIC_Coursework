fn main(){
	let vect1 : Vec<i32> = vec![1,2,3];
	foo(&vect1);

	println!("Vector : {:?}", vect1);
}

fn foo(vect : &Vec<i32>){
	println!("Vector : {:?}", vect);
}