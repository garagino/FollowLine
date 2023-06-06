# FollowLine PID
## 💻 Sobre o projeto
O projeto engloba o uso de robôs seguidores de linha, cuja operação é embasada em um sistema de controle PID. Essa abordagem garante a capacidade de realizar movimentos precisos e meticulosamente controlados. O robô  também é compatível com a tecnologia Bluetooth, o que possibilita o controle em tempo real dos valores do PID, proporcionando um ajuste instantâneo e eficaz.

## ⚙️ Hardware utilizado
<ul>
	<li>Ardu&iacute;no Uno/Nano - ATMEGA de 16Mhz</li>
	<li>Vespa - ESP32 de 240Mhz, com uma motor shield embutida para 2 motores DC **</li> 
	<li>QTR-8RC, array de 8 sensores digitais, produzida pela Pololu, cuja range varia entre 0 e 2500 para cada sensor individual</li>
	<li>Motor shield L298N, conhecida tamb&eacute;m por ponte H</li>
	<li>Ball caster</li>
	<li>Chassi feito em impressora 3D</li>
	<li>Baterias Li-Po e pilhas recarreg&aacute;veis de 3.7V, com suporte para duas pilhas.</li>
	<li>Motores DC de 6V/12V, 500RPM</li>
	<li>Interruptor</li>
</ul>
** Para o correto funcionamento desta placa, são necessários os devidos drivers e a biblioteca. Sendo assim, disponibilizamos o link que direciona ao processo de obtenção e instalação dos referidos drivers e da biblioteca:
https://www.robocore.net/tutoriais/instalacao-driver-da-blackboard

** Adicionalmente, segue o link fornecido pela fabricante, contendo tutoriais que demonstram de forma abrangente o uso dos recursos disponíveis, incluindo instruções detalhadas sobre como controlar os motores:
https://www.robocore.net/tutoriais/vespa/

## 📈 Parâmetros
Os parâmetros a seguir são recebidos pela comunicação Bluetooth, na qual o robô desempenha o papel de destinatário:

<table border="0" cellpadding="0" cellspacing="0" style="width:500px">
	<tbody>
		<tr>
			<td style="width:88px">run&nbsp;</td>
			<td style="width:398px">-&gt; Igni&ccedil;&atilde;o do rob&ocirc;</td>
		</tr>
		<tr>
			<td style="width:88px">stop&nbsp;</td>
			<td style="width:398px">-&gt; Parar o rob&ocirc;</td>
		</tr>
		<tr>
			<td style="width:88px">p = 2.5&nbsp;</td>
			<td style="width:398px">-&gt; Controle da proporcional</td>
		</tr>
		<tr>
			<td style="width:88px">i = 0.002</td>
			<td style="width:398px">-&gt; Controle da integrativa</td>
		</tr>
		<tr>
			<td style="width:88px">d = 5&nbsp;</td>
			<td style="width:398px">-&gt; Controle da derivativa</td>
		</tr>
		<tr>
			<td style="width:88px">speed = 255</td>
			<td style="width:398px">-&gt; Controle da velocidade</td>
		</tr>
		<tr>
			<td style="width:88px">line&nbsp;&nbsp;&nbsp;</td>
			<td style="width:398px">-&gt; Alternar entre seguir linha branca ou seguir linha preta. O padr&atilde;o &eacute; a linha preta, podendo ser alterada na programa&ccedil;&atilde;o.</td>
		</tr>
	</tbody>
</table>

Note que há parâmetros que devem possuir valores e outros parâmetros que não devem possuir valores.<br />
Os valores citados acima pelos parâmetros individuais do PID e speed são exemplos e cabe ao usuário fazer o uso correto dos valores baseado nas necessidades individuais de cada robô.<br/>

### Observações sobre os parâmetros
- Ao mudar qualquer um dos parâmetros do PID, o robô retorna o seguinte texto, baseado nos valores atuais da memória e incluindo o valor recentemente inserido: PID(P=2.00000, I=0.00200, D=5.00000).<br />
- Os parâmetros "run" e "stop" retornam: "Run robot.", "Stop robot.", respectivamente.<br />
- O parâmetro "line" retorna: "Following BLACK line." ou "Following WHITE line."<br />
- O parâmetro speed retorna o valor da velocidade máxima do robô <br />

## 😯 Como contribuir para o projeto

1. Faça um **fork** do projeto.
2. Crie uma nova branch com as suas alterações: `git checkout -b minha-funcionalidade`
3. Salve as alterações e crie uma mensagem de commit contando o que você fez: `git commit -m "Funcionalidade: Minha nova funcionalidade"`
4. Envie as suas alterações: `git push origin minha-funcionalidade`
> Caso tenha alguma dúvida confira este [guia de como contribuir no GitHub](https://github.com/firstcontributions/first-contributions)


## 📝 Licença

Este projeto esta sobe a licença MIT.
