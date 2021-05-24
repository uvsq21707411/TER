<!DOCTYPE html>
<html>
<head>
	<title>Vote</title>

</head>
<body>
	

	<form method="post"> 
		   <input type="text" name="Identifiant" id="Identifiant" placeholder="Votre identifiant" required> <br/><br/>
		   <input type="text" name="Vote" id="Vote" placeholder="Votre choix de vote" required> <br/><br/>
		   <input type="submit" name="formsend" id="formsend">
	</form>

	<?php
		


		if(isset($_POST['formsend'])) { 
			extract($_POST);

			   
			   if(!empty($Identifiant) && !empty($Vote)) {
			   		 echo "Merci, vous avez bien voté" ."<br/>" ;
			         echo "Votre vote:".$_POST['Vote'];


			         include 'include/database.php' ;
					 global $db;

					 $q = $db-> prepare("INSERT INTO vote(Identifiant,votes)VALUES(:Identifiant,:Vote)");

					  $q->execute([
					  'Identifiant'=>$Identifiant,
					  'Vote'=> $Vote
					  ]);

				}



		}


	?>





</body>

</html>




















































