# FollowLine PID
## 💻 Sobre o projeto
O projeto engloba o uso de robôs seguidores de linha, cuja operação é embasada em um sistema de controle PID. Essa abordagem garante a capacidade de realizar movimentos precisos e meticulosamente controlados. O robô  também é compatível com a tecnologia Bluetooth, o que possibilita o controle em tempo real dos valores do PID, proporcionando um ajuste instantâneo e eficaz.

## ⚙️ Hardware utilizado
<ul>
	<li>Ardu&iacute;no Uno/Nano - ATMEGA de 16Mhz</li>
	<li>Vespa - ESP32 de 240Mhz, com uma motor shield embutida para 2 motores DC *</li> 
	<li>QTR-8RC, array de 8 sensores digitais, produzida pela Pololu, cuja range varia entre 0 e 2500 para cada sensor individual **</li>
	<li>Motor shield L298N, conhecida tamb&eacute;m por ponte H</li>
	<li>Ball caster</li>
	<li>Chassi feito em impressora 3D</li>
	<li>Baterias Li-Po e pilhas recarreg&aacute;veis de 3.7V, com suporte para duas pilhas.</li>
	<li>Motores DC de 6V/12V, 500RPM</li>
	<li>Interruptor</li>
</ul>
* Para o correto funcionamento desta placa, são necessários os devidos drivers e a biblioteca. Sendo assim, disponibilizamos o link que direciona ao processo de obtenção e instalação dos referidos drivers e biblioteca, bem como tutoriais, no segundo link:<br>
https://www.robocore.net/tutoriais/instalacao-driver-da-blackboard<br>
https://www.robocore.net/tutoriais/vespa/<br>
<br>
** Biblioteca do sensor QTR-8RC da Pololu:<br>
https://github.com/pololu/qtr-sensors-arduino<br>

## 😯 Como contribuir para o projeto

1. Faça um **fork** do projeto.
2. Crie uma nova branch com as suas alterações: `git checkout -b minha-funcionalidade`
3. Salve as alterações e crie uma mensagem de commit contando o que você fez: `git commit -m "Funcionalidade: Minha nova funcionalidade"`
4. Envie as suas alterações: `git push origin minha-funcionalidade`
> Caso tenha alguma dúvida confira este [guia de como contribuir no GitHub](https://github.com/firstcontributions/first-contributions)


## 📝 Licença

Este projeto esta sobe a licença MIT.
