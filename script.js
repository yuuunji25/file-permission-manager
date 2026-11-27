console.log("File Permission Manager 시작");
let users=[];

function showRegister(){
  const content=document.getElementById("content");
  content.innerHTML=`<h2>사용자 등록</h2>
  <input type="text" id="username" placeholder="사용자 이름 입력">
  <button onclick="submitUser()">등록</button>`;


  const username=document.getElementById("username").value;

  if(username===""){
    alert("사용자 이름을 입력해주세요.");
    return;
  }
  users.push({username});
  document.getElementById("content").innerHTML+=`<p>${username} 등록 완료</p>`;
  alert("사용자가 등록되었습니다.");
}