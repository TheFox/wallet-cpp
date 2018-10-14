# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure('2') do |config|
  config.vm.box = 'generic/debian9'
  config.vm.box_check_update = false

  config.vm.hostname = 'wallet'

  config.vm.synced_folder '.', '/app'

  config.vm.provider 'virtualbox' do |vb|
    vb.gui = false
    vb.memory = 1024
  end

  config.vm.provision 'shell' do |s|
    s.env = {
      'DEBIAN_FRONTEND' => 'noninteractive',
      'WORKING_DIR' => '/app',
    }
    s.inline = <<-SHELL
      echo "cd ${WORKING_DIR}" >> /home/vagrant/.bashrc

      apt-get update -yqq
      apt-get upgrade -y
      apt-get install -y htop vim ack-grep lsof net-tools rsync clang

      echo 'done'
    SHELL
  end
end
